// http://ilyaraz.fatal.ru/src/brides.html
import java.io.*;
import java.util.*;

class Edge {
	public int source, target, capacity, flow, cost, index;
	public Edge reverse;
	public Edge(int source, int target, int capacity, int cost, int index) {
		this.source = source;
		this.target = target;
		this.capacity = capacity;
		this.cost = cost;
		this.index = index;
	}
}

class Brides {

	private int INFINITY = 1000000000;

	private int n, m, k, npath;
	private ArrayList<Edge>[] network;
	private int[] phi, best, path;
	private boolean[] mark;
	private Edge[] prev;

	private void addEdge(int index, int source, int target, int cost) {
		Edge p = new Edge(source, target, 1, cost, index);
		Edge q = new Edge(target, source, 0, -cost, index);
		p.reverse = q;
		q.reverse = p;
		network[source].add(p);
		network[target].add(q);
	}

	private void relax(Edge e) {
		if (e.flow < e.capacity && best[e.source] + e.cost + phi[e.source] - phi[e.target] < best[e.target]) {
			best[e.target] = best[e.source] + e.cost + phi[e.source] - phi[e.target];
			prev[e.target] = e;
		}
	}

	private void dfs(int cnode) {
		if (cnode == n - 1) return;
		for (Edge e : network[cnode])
			if (e.flow > 0) {
				dfs(e.target);
				e.flow = 0;
				path[npath++] = e.index;
				return;
			}
	}

	private void run() throws IOException {
		Scanner input = new Scanner(new File("brides.in"));
		n = input.nextInt();
		m = input.nextInt();
		k = input.nextInt();
		network = new ArrayList[n];
		for (int i = 0; i < n; i++)
			network[i] = new ArrayList<Edge>();
		for (int i = 0; i < m; i++) {
			int a = input.nextInt();
			int b = input.nextInt();
			int c = input.nextInt();
			addEdge(i + 1, a - 1, b - 1, c);
			addEdge(i + 1, b - 1, a - 1, c);
		}
		input.close();
		phi = new int[n];
		best = new int[n];
		mark = new boolean[n];
		prev = new Edge[n];
		for (int j = 0; j < k; j++) {
			for (int i = 0; i < n; i++) {
				best[i] = INFINITY;
				mark[i] = false;
			}
			best[0] = 0;
			prev[0] = null;
			for (;;) {
				int cnode = -1;
				for (int i = 0; i < n; i++)
					if (!mark[i] && (cnode == -1 || best[i] < best[cnode])) cnode = i;
				if (cnode == n - 1) break;
				mark[cnode] = true;
				for (Edge e : network[cnode]) relax(e);
			}
			if (best[n - 1] == INFINITY) {
				PrintWriter output = new PrintWriter(new File("brides.out"));
				output.println(-1);
				output.close();
				return;
			}
			for (int i = 0; i < n; i++)
				phi[i] += Math.min(best[i], best[n - 1]);
			Edge e = prev[n-1];
			while (e != null) {
				e.flow++;
				e.reverse.flow--;
				e = prev[e.source];
			}
		}
		double ans = 0;
		for (int i = 0; i < n; i++)
			for (Edge e : network[i]) ans += e.cost * e.flow;
		ans = ans / 2;
		PrintWriter output = new PrintWriter(new File("brides.out"));
		output.printf("%.10f\n", ans / k);
		path = new int[n];
		for (int i = 0; i < k; i++) {
			npath = 0;
			dfs(0);
			output.print(npath);
			for (int j = npath - 1; j >= 0; j--)
				output.print(" " + path[j]);
			output.println();
		}
		output.close();
	}

	public static void main(String[] a) {
		try {
			new Brides().run();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

}
