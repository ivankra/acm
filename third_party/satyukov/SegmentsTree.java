import java.io.*;
import java.util.*;

/**
 * Дерево отрезков (нумерация элементов с нуля, при реализации корень дерева - единица).
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
public class SegmentsTree implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	private static final String problemName = "query";
	private int n, dx;
	private int[] a;

	/**
	 * Добавляет к элементу с номером <code>where</code> число <code>value</code>.
	 * Элементы нумеруются с нуля (однако во внутреннем представлении - с соответствующей степени двойки).
	 */
	private void add(int where, int value) {
		where += dx;
		while (where >= 1) {
			a[where] += value;
			where = where >> 1;
		}
	}

	/**
	 * Считает сумму элементов с <code>from</code> по <code>to</code> включительно.
	 */
	private int calc(int from, int to) {
		int result = 0;
		from += dx;
		to += dx;
		while (from <= to) {
			if ((from & 1) == 1) {
				result += a[from];
				from++;
			}
			if ((to & 1) == 0) {
				result += a[to];
				to--;
			}
			from = from >> 1;
			to = to >> 1;
		}
		return result;
	}

	private void solve() throws IOException {
		in = new BufferedReader(new FileReader(new File(problemName + ".in")));
		out = new PrintWriter(new File(problemName + ".out"));
		
		n = Integer.parseInt(in.readLine());
		int k = 0;
		while ((1 << k) < n) {
			k++;
		}
		dx = 1 << k;
		a = new int[1 << (k + 1)];
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
		new Thread(new SegmentsTree()).start();
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
