package kiaedit;
import java.io.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import com.topcoder.shared.problem.*;

/*
 * TODO:
 *   * all created files should be readable only by the owner, i.e. mode 600
 *   * make backup copies on timer event, every N seconds.
 *   * do something about the double call to setProblemComponent()
 *     in practice rooms.
 */

public class KiaEdit {
    private static final String VERSION = "20081029";

    private com.topcoder.client.contestant.ProblemComponentModel arenaProblem = null;
    private com.topcoder.shared.language.Language arenaLanguage = null;
    private com.topcoder.shared.problem.Renderer arenaRenderer = null;
    private JPanel uiPanel;
    private JTextArea uiLog;
    private Map<String, String> settings = new HashMap();
    private Map<String, String> vars = new HashMap<String, String>();
    private String sourcePath = null;
    private String templateCode = null;
    private boolean setSourceFirstCall = false;
    private String lastBackupCode = null;

    private void loadSettings() {
        String[][] defaults;
        String home = System.getenv("HOME");

        if (home != null && home.startsWith("/home/")) {
            // POSIX-like system
            defaults = new String[][] {
                { "source.cc", "$HOME$/contest/p.cc" },
                { "source.java", "$HOME$/contest/$CLASSNAME$.java" },
                { "source.cs", "$HOME$/contest/p.cs" },
                { "template", "resource:/template.$EXT$" },
                { "footer", "resource:/footer.$EXT$" },
                { "backup", "/tmp/kiaedit/$CLASSNAME$-$TIME$.$EXT$" },
                { "problem.txt", "" },
                { "problem.html", "/tmp/kiaedit/$CLASSNAME$.html" },
                { "opencommands",
                  "/usr/bin/firefox /tmp/kiaedit/$CLASSNAME$.html\n" +
                  "/usr/bin/gvim \"$SOURCEPATH$\"" }
            };
        } else {
            defaults = new String[][] {
                { "source.cc", "C:\\contest\\p.cc" },
                { "source.java", "C:\\contest\\$CLASSNAME$.java" },
                { "source.cs", "C:\\contest\\csharp\\p.cs" },
                { "template", "resource:/template.$EXT$" },
                { "footer", "resource:/footer.$EXT$" },
                { "backup", "C:\\Temp\\KiaEdit-$CLASSNAME$-$TIME$.$EXT$" },
                { "problem.txt", "" },
                { "problem.html", "C:\\Temp\\$CLASSNAME$.html" },
                { "opencommands", "" }
            };
        }

        settings = new HashMap();
        for (String[] s : defaults) {
            settings.put(s[0], s[1]);
        }

        com.topcoder.client.contestApplet.common.LocalPreferences prefs;
        prefs = com.topcoder.client.contestApplet.common.LocalPreferences.getInstance();
        if (prefs == null) return;

        for (String[] s : defaults) {
            String res = prefs.getProperty("kiaedit.config." + s[0]);
            if (res != null) {
                settings.put(s[0], res);
            }
        }
    }

    private void saveSettings() {
        com.topcoder.client.contestApplet.common.LocalPreferences prefs;
        prefs = com.topcoder.client.contestApplet.common.LocalPreferences.getInstance();
        if (prefs == null) return;
        for (String key : settings.keySet()) {
            prefs.setProperty("kiaedit.config." + key, settings.get(key));
        }
    }

    private void log(String format, Object... args) {
        uiLog.setText(uiLog.getText() + String.format(format, args));
    }

    private String expand(String s) {
        vars.put("TIME", "" + System.currentTimeMillis());

        StringBuilder out = new StringBuilder();
        int p = 0, n = s.length();
        while (p < n) {
            if (s.charAt(p) == '$' && p+2 < n) {
                int q = p+1;
                while (q < n && Character.isLetter(s.charAt(q))) q++;

                String key = s.substring(p+1, q);
                if (q < n && s.charAt(q) == '$' && vars.containsKey(key)) {
                    out.append(vars.get(key));
                    p = q+1;
                    continue;
                }
            }

            out.append(s.charAt(p++));
        }

        return out.toString();
    }

    // Returns the contents of the specified file as a single String.
    // If the file doesn't exist returns an empty string.
    private static String readFile(String filename) {
        try {
            InputStream is = null;
            if (filename.startsWith("resource:")) {
                is = KiaEdit.class.getResourceAsStream(filename.substring(9));
            } else {
                File f = new File(filename);
                if (f.exists())
                    is = new FileInputStream(f);
            }
            if (is == null) {
                System.err.printf("readFile: can't open \"%s\"\n", filename);
                return null;
            }

            BufferedReader reader = new BufferedReader(new InputStreamReader(is));
            StringBuilder sb = new StringBuilder();
            while (true) {
                int c = reader.read();
                if (c == -1) break;
                sb.append((char)c);
            }
            reader.close();
            return sb.toString();
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    // Overwrites the contents of specified file with given String.
    private void writeFile(String filename, String data) {
        try {
            File f = new File(filename);
            File p = f.getParentFile();
            if (!p.exists()) p.mkdirs();                    
            FileWriter w = new FileWriter(f);
            w.write(data);
            w.close();
        } catch (Exception e) {
            log("Failed to create or overwrite file \"%s\":\n%s\n", filename, e);
        }
    }

    private String getType(DataType t) {
        return t.getDescriptor(arenaLanguage).replaceAll("vector +<", "vector<");
    }

    // Generates expansion for $METHODPARAMS$
    private String getParams() {
        DataType[] paramTypes = arenaProblem.getParamTypes();
        String[] paramNames = arenaProblem.getParamNames();

        String s = "";
        for (int i = 0; i < paramTypes.length; i++) {
            if (i > 0) s += ", ";
            s += getType(paramTypes[i]) + " " + paramNames[i];
        }
        return s;
    }

    // Escapes characters in input/output examples for embedding in C++ code
    private String escapeIO(String s) {
        StringBuilder out = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '\n' || s.charAt(i) == '\r') {
                out.append(" ");
            } else {
                if (s.charAt(i) == '\\' || s.charAt(i) == '\"')
                    out.append("\\");
                out.append(s.charAt(i));
            }
        }
        return out.toString();         
    }

    private String getJavaBoxedType(String s) {
        s = s.replaceAll("int", "Integer");
        s = s.replaceAll("long", "Long");
        s = s.replaceAll("double", "Double");
        s = s.replaceAll("char", "Character");
        s = s.replaceAll("boolean", "Boolean");
        return s;
    }

    private String newify(DataType dt, String s) {
        if (dt.getDimension() == 0) {
            return s;
        } else {
            boolean isJava = arenaLanguage instanceof com.topcoder.shared.language.JavaLanguage;
            if (isJava) {
                return "new " + getJavaBoxedType(getType(dt)) + s;
            } else {
                return "new " + getType(dt) + s;
            }
        }
    }

    // Generates expansion for $EXAMPLES$ and $IODECL$
    // These are specific to each language, and tied with testing code.
    private void generateFooterVars() {
        DataType tcRet = arenaProblem.getReturnType(); 
        String ret = getType(tcRet);

        DataType[] tcPar = arenaProblem.getParamTypes();

        String[] par = new String[tcPar.length];
        for (int i = 0; i < par.length; i++)
            par[i] = getType(tcPar[i]);

        TestCase[] cs = arenaProblem.getTestCases();

        boolean isJava = arenaLanguage instanceof com.topcoder.shared.language.JavaLanguage;
        boolean isSharp = arenaLanguage instanceof com.topcoder.shared.language.CSharpLanguage;

        if (isJava || isSharp) {
            String s = "if (input." + (isJava ? "l" : "L") + "ength != " + par.length + ") " +
                "throw new Exception(\"Bad number of parameters for call\");\n";

            // result = instance.myMethod((int)input[0], (int)input[1]);
            s += "result = instance." + arenaProblem.getMethodName() + "(";
            for (int i = 0; i < par.length; i++) {
                String type = isJava ? getJavaBoxedType(par[i]) : par[i];
                s += (i > 0 ? ", " : "") + "(" + type + ")input[" + i + "]";
            }
            s += ");\n";
            vars.put("IODECL", s);

            // new Example("Example 0", new object[]{123, 456}, 579)
            StringBuilder out = new StringBuilder();
            for (int i = 0; i < cs.length; i++) {
                out.append(isJava ? "{" : "new Example(");
                out.append("\"Example " + i + "\", new " + (isJava ? "O" : "o") + "bject[]{");
                String[] in = cs[i].getInput();
                for (int j = 0; j < in.length; j++) {
                    if (j > 0) out.append(", ");
                    out.append(newify(tcPar[j], in[j]));
                }
                String ans = cs[i].getOutput();
                out.append("}, " + newify(tcRet, ans) + (isJava ? "}" : ")"));
                out.append(i+1 < cs.length ? ",\n" : "\n");
            }
            vars.put("EXAMPLES", out.toString());
        } else {
            // C++
            StringBuilder out = new StringBuilder();
            out.append("struct InputTuple {\n");
            for (int i = 0; i < par.length; i++)
                out.append("\t" + par[i] + " arg" + (i+1) + ";\n");
            out.append("};\n\n");
            out.append("template<> void Read(InputTuple &out, istream &s) {\n");
            for (int i = 0; i < par.length; i++) {
                if (i > 0) out.append("\tSkip(s, ',');\n");
                out.append("\tRead(out.arg" + (i+1) + ", s);\n");
            }
            out.append("}\n\n");
            out.append("template<> void Write(ostream &s, const InputTuple &in) {\n");
            for (int i = 0; i < par.length; i++) {
                if (i > 0) out.append("\ts << \", \";\n");
                out.append("\tWrite(s, in.arg" + (i+1) + ");\n");
            }
            out.append("}\n\n");
            out.append("typedef " + ret + " OutputType;\n\n");
            out.append("OutputType Execute(InputTuple input) {\n");
            out.append("\t" + arenaProblem.getClassName() + " instance;\n");
            out.append("\treturn instance." + arenaProblem.getMethodName() + "(");
            for (int i = 0; i < par.length; i++)
                out.append((i > 0 ? ", " : "") + "input.arg" + (i+1));
            out.append(");\n}\n\n");
            vars.put("IODECL", out.toString());

            out = new StringBuilder();
            for (int n = 0; n < cs.length; n++) {
                String[] in = cs[n].getInput();
                out.append("\"");
                for (int i = 0; i < in.length; i++) {
                    if (i > 0) out.append(", ");
                    out.append(escapeIO(in[i]));
                }
                out.append(" Returns: " + escapeIO(cs[n].getOutput()));
                out.append("\"");
                if (n+1 < cs.length) out.append(",");
                out.append("\n");
            }
            vars.put("EXAMPLES", out.toString());
        }
    }

    // Makes a backup copy of the main source file
    private void makeBackup() {
        if (arenaProblem == null) return;

        String path = settings.get("backup");
        if (path == null || path.length() == 0) return;

        path = expand(path);

        String src = readFile(sourcePath);
        if (src == null || src.length() == 0) return;

        synchronized (this) {
            if (src.equals(lastBackupCode)) return;
            lastBackupCode = src;
        }
 
        writeFile(path, src);
    }

    private String getFooter() {
        String footerPath = expand(settings.get("footer"));
        String s = readFile(footerPath);
        return s == null ? "" : expand(s);
    }

    private String generateTemplateCode() {
        String templatePath = expand(settings.get("template"));
        String s = readFile(templatePath);
        String source = (s == null) ? "" : expand(s);
        if (source.length() == 0) {
            log("Template file (%s) is missing or empty.\n", templatePath);
            return "";
        } else {
            return source + getFooter();
        }
    }

    // Public API

    public KiaEdit() {
        loadSettings();

        uiLog = new JTextArea();
        uiLog.setForeground(Color.green);
        uiLog.setBackground(Color.black);

        uiPanel = new JPanel(new BorderLayout());
        uiPanel.setPreferredSize(new Dimension(800, 32));
        uiPanel.add(new JScrollPane(uiLog), BorderLayout.CENTER);

        JButton btn = new JButton("Write template");
        btn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (arenaProblem != null) {
                    makeBackup();
                    templateCode = generateTemplateCode();
                    writeFile(sourcePath, templateCode);
                    log("Source code has been written to " + sourcePath + "\n");
                }
            }
        });
        JPanel tmp = new JPanel();
        tmp.add(btn);
        uiPanel.add(tmp, BorderLayout.WEST);

        vars.put("VERSION", VERSION);
        log("KiaEdit v." + VERSION + "\n");
    }

    public JPanel getEditorPanel() {
        return uiPanel;
    }

    public String getSource() {
        if (arenaProblem == null) return "";

        makeBackup();

        StringBuilder out = new StringBuilder();
        boolean cut = false;

        String bc = "// BEGIN CUT HERE";
        String ec = "// END CUT HERE";

        String originalSource = readFile(sourcePath);
        if (originalSource == null)
            originalSource = "";

        String[] lines = originalSource.split("\n");
        for (String s : lines) {
            if (s.startsWith(bc))
                cut = true;
            else if (s.startsWith(ec))
                cut = false;
            else if (!cut)
                out.append(s + "\n");
        }

        return out.toString();
    }
    
    public static ArrayList<String> splitQuotedString(String s) {
        ArrayList<String> res = new ArrayList<String>();
        for (int i = 0; i < s.length();) {
            if (Character.isWhitespace(s.charAt(i))) {
                i++;
                continue;                
            }
            
            StringBuilder sb = new StringBuilder();
            if (s.charAt(i) == '"') {
                i++;
                while (i < s.length() && s.charAt(i) != '"') {
                    if (i+1 < s.length() && s.charAt(i) == '\\' &&
                            s.charAt(i+1) == '\"') {
                        sb.append('"');
                        i += 2;
                    } else {
                        sb.append(s.charAt(i));
                        i++;
                    }
                }
                if (i < s.length() && s.charAt(i) == '"') i++;                
            } else {
                while (i < s.length() && !Character.isWhitespace(s.charAt(i))) {
                    sb.append(s.charAt(i));
                    i++;
                }
            }
            res.add(sb.toString());          
        }
        return res;
    }

    public void setSource(String source) {
        if (arenaProblem == null) return;
        if (source == null) source = "";

        makeBackup();

        templateCode = generateTemplateCode();

        String code;
        if (source.length() == 0) {
            code = templateCode;
        } else {
            code = source + getFooter();
        }
        writeFile(sourcePath, code);

        log("Source code is written to " + sourcePath + "\n");

        if (setSourceFirstCall) {
            setSourceFirstCall = false;
            for (String command : expand(settings.get("opencommands")).split("\n")) {
                ArrayList<String> v = splitQuotedString(command);
                if (v.size() == 0) continue;
                ProcessBuilder pb = new ProcessBuilder(v);
                try {
                    Process process = pb.start();
                } catch (Exception e) {
                    log("Can't execute " + command + ":\n" + e.toString() + "\n");
                }
            }

            log("Good luck and have fun!\n");            
        }
    }

    public void setProblemComponent(
            com.topcoder.client.contestant.ProblemComponentModel problem,
            com.topcoder.shared.language.Language lang,
            com.topcoder.shared.problem.Renderer renderer) {

        makeBackup();

        arenaProblem = problem;
        arenaLanguage = lang;
        arenaRenderer = renderer;

        if (arenaProblem == null) return;

        log("You are opening problem " + arenaProblem.getClassName() + "\n");

        String ext = "cc";
        if (arenaLanguage instanceof com.topcoder.shared.language.JavaLanguage) {
            ext = "java";
        } else if (arenaLanguage instanceof com.topcoder.shared.language.CSharpLanguage) {
            ext = "cs";
        } else if (!(arenaLanguage instanceof com.topcoder.shared.language.CPPLanguage)) {
            log("Sorry, %s is not supported.\n", arenaLanguage.getName());
            log("Choose a different language or a different editor.\n");
            // continue with .cc anyway
        }

        vars.put("EXT", ext);
        vars.put("CLASSNAME", problem.getClassName());
        vars.put("METHODNAME", problem.getMethodName());
        vars.put("METHODPARAMS", getParams());
        vars.put("RETURNTYPE", getType(problem.getReturnType()));

        String home = System.getenv("HOME");
        if (home != null)
            vars.put("HOME", home);
        
        sourcePath = expand(settings.get("source." + ext));
        vars.put("SOURCEPATH", sourcePath);

        generateFooterVars();    // EXAMPLES and IODECL

        vars.put("PROBLEMHTML", "");
        try {
            String html = arenaRenderer.toHTML(arenaLanguage);
            String title = vars.get("CLASSNAME") + " (" + arenaLanguage.getName() + ")";
            if (html.startsWith("<html><body")) {
                html = "<html><head><title>" + title + "</title></head>"
                    + html.substring(6);
            }
            vars.put("PROBLEMHTML", html);
        } catch (Exception e) {}

        vars.put("PROBLEMTEXT", "");
        try {
            vars.put("PROBLEMTEXT", arenaRenderer.toPlainText(arenaLanguage));
        } catch (Exception e) {}

        String path = settings.get("problem.txt");
        if (path != null && path.length() != 0)
            writeFile(expand(path), vars.get("PROBLEMTEXT"));

        path = settings.get("problem.html");
        if (path != null && path.length() != 0)
            writeFile(expand(path), vars.get("PROBLEMHTML"));

        setSourceFirstCall = true;
        lastBackupCode = null;
    }

    public void configure() {
        kiaedit.ConfigDialog w = new kiaedit.ConfigDialog(null, settings);
        w.setVisible(true);
        settings = w.getValues();
        saveSettings();
    }

    private static void showHelp(boolean terminateOnClose) {
        String help = readFile("resource:/KiaEdit.html");
        if (help == null || help == "") {
            if (terminateOnClose) System.exit(1);
            return;
        }

        JEditorPane htmlPane = new JEditorPane();
        htmlPane.setContentType("text/html");
        htmlPane.setText(help);
        htmlPane.setEditable(false);
        htmlPane.setPreferredSize(new Dimension(800, 600));

        JScrollPane scrollPane = new JScrollPane(htmlPane);

        JPanel panel = new JPanel();
        panel.setLayout(new BorderLayout());
        panel.setBorder(BorderFactory.createEmptyBorder(16, 16, 16, 16));
        panel.add(scrollPane, BorderLayout.CENTER);

        JFrame frame = new JFrame("KiaEdit Help - KiaEdit v." + VERSION);
        frame.setDefaultCloseOperation(terminateOnClose ? JFrame.EXIT_ON_CLOSE : JFrame.DISPOSE_ON_CLOSE);
        frame.add(panel);
        frame.pack();
        frame.setVisible(true);

        scrollPane.getVerticalScrollBar().setValue(0);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                showHelp(true);
            }
        });
    }
}
