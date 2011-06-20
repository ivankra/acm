import java.io.*;
import java.util.*;

/**
 * Поиск точек сочленения (неориентированный граф, способ представления - список ребер).
 * Время работы: O(E).
 * 
 * @author Roman V Satyukov
 */
public class ArticulationPoints implements Runnable {
    private BufferedReader in;
    private PrintWriter out;
    private static final String problemName = "ap";
    
    private class Graph {
        private int n;
        private int[] head;
        private int[] next;
        private int[] target;
        private int[] enter;
        private boolean[] isAP;
        private int edgesNumber;
        private int curTime;
        private int root;
        public static final int inf = Integer.MAX_VALUE / 2 - 1;
        
        private int dfs(int u) {
            enter[u] = curTime++;
            int result = enter[u];
            int sons = 0;
            for (int cur = head[u]; cur != -1; cur = next[cur]) {
                int v = target[cur];
                if (enter[v] == -1) {
                    int tmp = dfs(v);
                    sons++;
                    if (u != root && tmp >= enter[u]) {
                        isAP[u] = true;
                    }
                    result = Math.min(result, tmp);
                } else {
                    result = Math.min(result, enter[v]);
                }
            }
            if (u == root && sons > 1) {
                isAP[u] = true;
            }
            return result;
        }
        
        public Graph(int n, int m) {
            this.n = n;
            head = new int[n];
            next = new int[m];
            target = new int[m];
            enter = new int[n];
            Arrays.fill(enter, -1);
            Arrays.fill(head, -1);
            edgesNumber = 0;
        }

        public void addEdge(int u, int v) {
            target[edgesNumber] = v;
            next[edgesNumber] = head[u];
            head[u] = edgesNumber++;
        }
        
        public boolean[] findAP() {
            curTime = 0;
            isAP = new boolean[n];
            for (int i = 0; i < n; i++) {
                if (enter[i] == -1) {
                    root = i;
                    dfs(i);
                }
            }
            return isAP;
        }
    }

    private void solve() throws IOException {
        in = new BufferedReader(new FileReader(new File(problemName + ".in")));
        out = new PrintWriter(new File(problemName + ".out"));
        
        StringTokenizer st = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        Graph g = new Graph(n, 2 * m);
        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(in.readLine());
            int u = Integer.parseInt(st.nextToken()) - 1;
            int v = Integer.parseInt(st.nextToken()) - 1;
            g.addEdge(u, v);
            g.addEdge(v, u);
        }
        boolean[] isAP = g.findAP();
        for (int i = 0; i < n; i++) {
            if (isAP[i]) {
                out.print((i + 1) + " ");
            }
        }
        out.println();
        
        in.close();
        out.close();
    }

    public void run() {
        try {
            solve();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
    
    public static void main(String[] args) {
        new Thread(new ArticulationPoints()).start();
    }
}
