import java.io.*;
import java.util.*;

/**
 * Поиск максимального потока в сети с помощью разновидности алгоритма
 * маштабирования. Сеть представляется с помощью списка ребер (ArrayList+Edge).
 * Пример входного файла (из Кормена, 6 вершин, 10 ребер, поток из 1 в 6):
 *   6 10
 *   1 2 16
 *   2 3 12
 *   3 6 20
 *   1 5 13
 *   5 4 14
 *   4 6 4
 *   4 3 7
 *   3 5 9
 *   2 5 10
 *   5 2 4
 *   1 6
 * 
 * @author Roman V Satyukov
 */
public class MaxFlow2 implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	private static final String problemName = "maxflow";
	
	private class Graph {
		private ArrayList<Edge>[] edges;
		public static final int inf = Integer.MAX_VALUE / 2 - 1;
		private boolean[] mark;
		private int limit;
		
		private class Edge {
			public int u, v, cap, flow;
			public Edge rev;
			
			public Edge(int u, int v, int cap) {
				this.u = u;
				this.v = v;
				this.cap = cap;
			}
		}
		
		@SuppressWarnings("unchecked")
		public Graph(int n) {
			edges = new ArrayList[n];
			mark = new boolean[n];
			for (int i = 0; i < n; i++) {
				edges[i] = new ArrayList<Edge>();
			}
		}
		
		public void addEdge(int u, int v, int cap) {
			Edge e1 = new Edge(u, v, cap);
			Edge e2 = new Edge(v, u, 0);
			e1.rev = e2;
			e2.rev = e1;
			edges[u].add(e1);
			edges[v].add(e2);
		}
		
		public int maxFlow(int s, int t) {
			int result = 0;
			
			limit = inf;
			while (limit > 0) {
				Arrays.fill(mark, false);
				if (!dfs(s, t)) {
					limit >>= 1;
				} else {
					result += limit;
				}
			}
			
			return result;
		}

		private boolean dfs(int u, int t) {
			if (u == t) {
				return true;
			}
			
			mark[u] = true;
			for (Edge e: edges[u]) {
				if (!mark[e.v] && e.flow + limit <= e.cap && dfs(e.v, t)) {
					e.flow += limit;
					e.rev.flow -= limit;
					return true;
				}
			}
			
			return false;
		}
	}

	private void solve() throws IOException {
		in = new BufferedReader(new FileReader(new File(problemName + ".in")));
		out = new PrintWriter(new File(problemName + ".out"));
		
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		Graph g = new Graph(n);
		for (int i = 0; i < m; i++) {
			st = new StringTokenizer(in.readLine());
			int u = Integer.parseInt(st.nextToken()) - 1;
			int v = Integer.parseInt(st.nextToken()) - 1;
			int cap = Integer.parseInt(st.nextToken());
			g.addEdge(u, v, cap);
		}
		st = new StringTokenizer(in.readLine());
		int source = Integer.parseInt(st.nextToken()) - 1;
		int target = Integer.parseInt(st.nextToken()) - 1;
		out.println(g.maxFlow(source, target));
		
		in.close();
		out.close();
	}

	public static void main(String[] args) {
		new Thread(new MaxFlow2()).start();
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
