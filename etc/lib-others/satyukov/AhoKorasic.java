import java.io.*;
import java.util.*;

/**
 * Алгоритм Ахо-Корасик.
 * Ищет все вхождения набора строк <code>pattern</code> в строку <code>text</code>.
 * Формат входного файла (aho.in):
 *   text
 *   pattern_1
 *   pattern_2
 *   ...
 *   pattern_n
 *
 * @author Roman V Satyukov
 */
public class AhoKorasic implements Runnable {
    private BufferedReader in;
    private PrintWriter out;
    private static final String problemName = "aho";
    
    private int[] head;
    private int[] target;
    private int[] next;
    private char[] ch;
    private int[] suffLink;
    private int[] parent;
    private int[] finish;
    private int[] liftUp;
    private ArrayList<String> patterns;
    private int edges;
    private int vertices;
    
    private int go(int u, char c) {
        for (int edge = head[u]; edge != -1; edge = next[edge]) {
            if (ch[edge] == c) {
                return target[edge];
            }
        }
        return -1;
    }
    
    private void addPattern(String pattern, int number) {
        int cur = 0;
        for (int i = 0; i < pattern.length(); i++) {
            char c = pattern.charAt(i);
            int newCur = go(cur, c);
            if (newCur == -1) {
                target[edges] = vertices;
                ch[edges] = c;
                next[edges] = head[cur];
                head[cur] = edges;
                newCur = vertices;
                parent[vertices] = cur;
                vertices++;
                edges++;
            }
            cur = newCur;
        }
        finish[cur] = number;
    }
    
    private void calcSuffLinks(int u) {
        if (parent[u] == -1) {
            suffLink[u] = -1;
            return;
        }
        int p = parent[u];
        if (p == 0) {
            suffLink[u] = 0;
            return;
        }
        char prevChar = 0;
        for (int edge = head[p]; edge != -1; edge = next[edge]) {
            if (target[edge] == u) {
                prevChar = ch[edge];
            }
        }
        p = suffLink[p];
        int result = -1;
        while (p != -1) {
            result = go(p, prevChar);
            if (result != -1) {
                break;
            }
            p = suffLink[p];
        }
        suffLink[u] = (result == -1 ? 0 : result);
    }

    private int calcLiftUp(int u) {
        if (liftUp[u] != -2) {
            return liftUp[u];
        }
        if (u == 0) {
            liftUp[u] = -1;
            return -1;
        }
        int p = suffLink[u];
        liftUp[u] = (finish[p] != -1) ? p : calcLiftUp(p);
        return liftUp[u]; 
    }

    private void readPatterns() throws IOException {
        patterns = new ArrayList<String>();
        int totalSize = 0;
        while (true) {
            String cur = in.readLine();
            if (cur == null) {
                break;
            }
            patterns.add(cur);
            totalSize += cur.length();
        }
        head = new int[totalSize + 1];
        next = new int[totalSize + 1];
        target = new int[totalSize + 1];
        ch = new char[totalSize + 1];
        suffLink = new int[totalSize + 1];
        parent = new int[totalSize + 1];
        finish = new int[totalSize + 1];
        liftUp = new int[totalSize + 1];
        Arrays.fill(head, -1);
        Arrays.fill(next, -1);
        Arrays.fill(finish, -1);
        edges = 0;
        vertices = 1;
        parent[0] = -1;
        int number = 0;
        for (String cur: patterns) {
            addPattern(cur, number++);
        }
        for (int i = 0; i < vertices; i++) {
            calcSuffLinks(i);
        }
        Arrays.fill(liftUp, -2);
        for (int i = 0; i < vertices; i++) {
            calcLiftUp(i);
        }
    }
    
    private int step(int cur, char ch) {
        int result = go(cur, ch); 
        if (result != -1) {
            return result;
        }
        if (cur == 0) {
            return 0;
        }
        return step(suffLink[cur], ch);
    }
    
    private void printMatch(int pattern, int endPos) {
        int from = (endPos - patterns.get(pattern).length() + 1);
        out.println("Pattern " + pattern + ": Found match at position [" + from + ".." + endPos + "]");
    }

    private void solve() throws IOException {
        in = new BufferedReader(new FileReader(new File(problemName + ".in")));
        out = new PrintWriter(new File(problemName + ".out"));
        
        char[] text = in.readLine().toCharArray();
        readPatterns();
        int cur = 0;
        for (int i = 0; i < text.length; i++) {
            cur = step(cur, text[i]);
            if (finish[cur] != -1) {
                printMatch(finish[cur], i);
            }
            for (int tmp = liftUp[cur]; tmp != -1; tmp = liftUp[tmp]) {
                printMatch(finish[tmp], i);
            }
        }
        
        in.close();
        out.close();
    }

    public static void main(String[] args) {
        new Thread(new AhoKorasic()).start();
    }
    
    public void run() {
        try {
            solve();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}
