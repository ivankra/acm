import java.io.*;
import java.util.*;

/**
 * Поиск максимального потока в сети с помощью разновидности алгоритма
 * маштабирования. Сеть представляется с помощью списка ребер (в массивах).
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
public class MaxFlow1 implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	private static final String problemName = "maxflow";
	
	private class Graph {
		private int[] head;
		private int[] next;
		private int[] target;
		private int[] flow;
		private int[] cap;
		private int[] rev;
		private boolean[] mark;
		private int edgesNumber;
		private int limit;
		public static final int inf = Integer.MAX_VALUE / 2 - 1;
		
		public Graph(int n, int m) {
			head = new int[n];
			next = new int[2 * m];
			target = new int[2 * m];
			flow = new int[2 * m];
			cap = new int[2 * m];
			rev = new int[2 * m];
			mark = new boolean[n];
			Arrays.fill(head, -1);
			edgesNumber = 0;
		}

		public void addEdge(int u, int v, int c) {
			target[edgesNumber] = v;
			cap[edgesNumber] = c;
			next[edgesNumber] = head[u];
			head[u] = edgesNumber++;

			target[edgesNumber] = u;
			cap[edgesNumber] = 0;
			next[edgesNumber] = head[v];
			head[v] = edgesNumber++;
			
			rev[edgesNumber - 1] = edgesNumber - 2;
			rev[edgesNumber - 2] = edgesNumber - 1;
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
			for (int cur = head[u]; cur != -1; cur = next[cur]) {
				int v = target[cur];
				if (!mark[v] && flow[cur] + limit <= cap[cur] && dfs(v, t)) {
					flow[cur] += limit;
					flow[rev[cur]] -= limit;
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
		Graph g = new Graph(n, m);
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
		new Thread(new MaxFlow1()).start();
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
