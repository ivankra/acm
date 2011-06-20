import java.io.*;
import java.util.*;

/**
 * Поиск компонент реберной двусвязности (неориентированный граф, способ представления - список ребер).
 * Время работы: O(E).
 * 
 * @author Roman V Satyukov
 */
public class TwoEdgeConnectivityComponents implements Runnable {
    private BufferedReader in;
    private PrintWriter out;
    private static final String problemName = "2connectivity";
    
    private class Graph {
        private int n;
        private int[] head;
        private int[] next;
        private int[] target;
        private boolean[] used;
        private int[] time;
        private int[] colour;
        private int edgesNumber;
        private int curTime;
        private int curColour;
        public static final int inf = Integer.MAX_VALUE / 2 - 1;
        
        private void dfs1(int u) {
        	colour[u] = 0;
            for (int cur = head[u]; cur != -1; cur = next[cur]) {
                int v = target[cur];
                if (colour[v] == -1) {
                	used[cur] = true;
                	dfs1(v);
                }
            }
            time[curTime++] = u;
        }
        
		private void dfs2(int u) {
        	colour[u] = curColour;
            for (int cur = head[u]; cur != -1; cur = next[cur]) {
            	if (used[cur]) {
            		continue;
            	}
                int v = target[cur];
                if (colour[v] == 0) {
                	dfs2(v);
                }
            }
		}
		
        public Graph(int n, int m) {
            this.n = n;
            head = new int[n];
            next = new int[m];
            target = new int[m];
            time = new int[n];
            colour = new int[n];
            used = new boolean[m];
            Arrays.fill(head, -1);
            edgesNumber = 0;
        }

        public void addEdge(int u, int v) {
            target[edgesNumber] = v;
            next[edgesNumber] = head[u];
            head[u] = edgesNumber++;
        }
        
        public int[] findTwoEdgeConnectivityComponenets() {
            curTime = 0;
            Arrays.fill(colour, -1);
            Arrays.fill(used, false);
            for (int i = 0; i < n; i++) {
            	if (colour[i] == -1) {
            		dfs1(i);
            	}
            }
            Arrays.fill(colour, 0);
            curColour = 0;
            for (int i = n - 1; i >= 0; i--) {
            	int u = time[i];
            	if (colour[u] == 0) {
            		curColour++;
            		dfs2(u);
            	}
            }
            return colour.clone();
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
        
        int[] components = g.findTwoEdgeConnectivityComponenets();
        for (int i = 0; i < n; i++) {
        	out.print(components[i] + " ");
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
        new Thread(new TwoEdgeConnectivityComponents()).start();
    }
}
