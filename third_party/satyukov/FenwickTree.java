import java.io.*;
import java.util.*;

/**
 * Дерево Фенвика (нумерация элементов с нуля).
 * Пример входного файла:
 *   4
 *   add 0 1
 *   add 1 2
 *   add 2 4
 *   add 3 8
 *   sum 0 3
 *   end
 * В примере сначала "создается" массив из четырех элементов. После чего он заполняется степенями
 * двойки (1 2 4 8). Затем считается сумма всех элементов.
 *   
 * @author Roman V Satyukov
 */
public class FenwickTree implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	private static final String problemName = "query";
	private int[] a;
	private int n;

	/**
	 * Добавляет к элементу с номером <code>where</code> число <code>value</code>.
	 * Элементы нумеруются с нуля.
	 */
	private void add(int where, int value) {
		for (int u = where; u < n; u = (u | (u + 1))) {
			a[u] += value;
		}
	}

	/**
	 * Считает сумму элементов с <code>0</code> по <code>to</code> включительно.
	 */
	private int calc(int to) {
		int result = 0;
		for (int u = to; u >= 0; u = (u & (u + 1)) - 1) {
			result += a[u];
		}
		return result;
	}

	/**
	 * Считает сумму элементов с <code>from</code> по <code>to</code> включительно.
	 */
	private int calc(int from, int to) {
		if (from == 0) {
			return calc(to);
		} else {
			return calc(to) - calc(from - 1);
		}
	}

	private void solve() throws IOException {
		in = new BufferedReader(new FileReader(new File(problemName + ".in")));
		out = new PrintWriter(new File(problemName + ".out"));
		
		n = Integer.parseInt(in.readLine());
		a = new int[n];
		while (true) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			String action = st.nextToken();
			if (action.equals("add")) {
				int where = Integer.parseInt(st.nextToken());
				int value = Integer.parseInt(st.nextToken());
				add(where, value);
			} else if (action.equals("sum")) {
				int from = Integer.parseInt(st.nextToken());
				int to = Integer.parseInt(st.nextToken());
				out.println("Sum a[" + from + ".." + to + "] = " + calc(from, to));
			} else {
				break;
			}
		}
		
		in.close();
		out.close();
	}

	public static void main(String[] args) {
		new Thread(new FenwickTree()).start();
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
