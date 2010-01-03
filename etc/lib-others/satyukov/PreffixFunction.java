import java.io.*;

/**
 * Вычисление префикс-функции для строки (строка задается во входном файле preffix.in).
 * 
 * @author Roman V Satyukov
 */
public class PreffixFunction implements Runnable {
    private BufferedReader in;
    private PrintWriter out;
    private static final String problemName = "preffix";

    private void solve() throws IOException {
        in = new BufferedReader(new FileReader(new File(problemName + ".in")));
        out = new PrintWriter(new File(problemName + ".out"));
        
        char[] text = in.readLine().toCharArray();
        int n = text.length;
        int[] p = new int[n];
        int k = 0;
        for (int i = 1; i < n; i++) {
            while (k > 0 && text[k] != text[i]) {
                k = p[k - 1];
            }
            if (text[k] == text[i]) {
                k++;
            }
            p[i] = k;
        }
        for (int i = 0; i < n; i++) {
            out.print(p[i] + " ");
        }
        out.println();
        
        in.close();
        out.close();
    }

    public static void main(String[] args) {
        new Thread(new PreffixFunction()).start();
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
