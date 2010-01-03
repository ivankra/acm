import java.io.*;
import java.util.*;

/**
 * ѕоиск максимального паросочетани€ в двудольном графе. √раф хранитс€ в виде
 * матрицы смежности: w[i,j] - есть ли ребро из вершины i левой доли в
 * вершину j правой доли. ¬рем€ работы: O(V^3).
 * ‘ормат входного файла: (matching.in)
 *   Ќа первой строке - число вершин в левой доле (n), число вершин в правой
 *   доле (m). ƒалее на следующих n строках - описание ребер. Ќа i-ой строке
 *   записаны номера вершин из правой доли, с которыми соединена вершина i
 *   из левой доли.
 * 
 * @author Roman V Satyukov
 */
public class MaxMatching implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	private static final String problemName = "matching";
	
	private int n, m;
	private boolean[][] w;
	private int[] lm;
	private int[] rm;
	private boolean[] mark;
	
	private boolean dfs(int u) {
		for (int v = 0; v < m; v++) {
			if (w[u][v] && !mark[v]) {
				mark[v] = true;
				if (rm[v] == -1 || dfs(rm[v])) {
					lm[u] = v;
					rm[v] = u;
					return true;
				}
			}
		}
		return false;
	}

	private void solve() throws IOException {
		in = new BufferedReader(new FileReader(new File(problemName + ".in")));
		out = new PrintWriter(new File(problemName + ".out"));
		
		StringTokenizer st = new StringTokenizer(in.readLine());
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		w = new boolean[n][m];
		for (int i = 0; i < n; i++) {
			st = new StringTokenizer(in.readLine());
			while (st.hasMoreTokens()) {
				int u = Integer.parseInt(st.nextToken()) - 1;
				w[i][u] = true;
			}
		}
		lm = new int[n];
		rm = new int[m];
		mark = new boolean[m];
		Arrays.fill(lm, -1);
		Arrays.fill(rm, -1);
		int matchingSize = 0;
RESTART:		
		while (true) {
			Arrays.fill(mark, false);
			for (int i = 0; i < n; i++) {
				if (lm[i] == -1 && dfs(i)) {
					matchingSize++;
					continue RESTART;
				}
			}
			break;
		}
		out.println(matchingSize);
		for (int i = 0; i < n; i++) {
			if (lm[i] != -1) {
				out.println((i + 1) + " <-> " + (lm[i] + 1));
			}
		}
		
		in.close();
		out.close();
	}

	public static void main(String[] args) {
		new Thread(new MaxMatching()).start();
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
