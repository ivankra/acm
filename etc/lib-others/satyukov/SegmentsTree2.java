import java.io.*;
import java.util.*;

/**
 * Дерево отрезков (нумерация элементов с нуля, при реализации корень дерева - единица).
 * Пример входного файла:
 *   4
 *   set 0 2 1
 *   set 1 3 2
 *   sum 0 3
 *   end
 * В примере сначала "создается" массив из четырех элементов. После чего элементы с нулевого
 * по второй заполняются единицами, а с первого по третий - двойками. 
 * Затем считается сумма всех элементов.
 *   
 * @author Roman V Satyukov
 */
public class SegmentsTree2 implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	private static final String problemName = "query2";
	private int n, k, dx;
	private int[] a;
	private boolean[] mark;

	private void set(int root, int depth, int from, int to, int value) {
		int low = root << depth;
		int hi = ((root + 1) << depth) - 1;
		if (to < low || from > hi) {
			return;
		}
		if (from <= low && hi <= to) {
			mark[root] = true;
			a[root] = value << depth;
			return;
		}
		int root2 = root << 1;
		if (mark[root]) {
			mark[root2] = true;
			mark[root2 + 1] = true;
			a[root2] = a[root] >> 1;
			a[root2 + 1] = a[root] >> 1;
			mark[root] = false;
		}
		set(root2, depth - 1, from, to, value);
		set(root2 + 1, depth - 1, from, to, value);
		a[root] = a[root2] + a[root2 + 1];
	}
	
	/**
	 * Устанавливает элементы с <code>from</code> по <code>to</code> равными числу <code>value</code>.
	 * Элементы нумеруются с нуля (однако во внутреннем представлении - с соответствующей степени двойки).
	 */
	private void set(int from, int to, int value) {
		from += dx;
		to += dx;
		set(1, k, from, to, value);
	}
	
	private int calc(int root, int depth, int from, int to) {
		int low = root << depth;
		int hi = ((root + 1) << depth) - 1;
		if (to < low || from > hi) {
			return 0;
		}
		if (from <= low && hi <= to) {
			return a[root];
		}
		if (mark[root]) {
			return (a[root] >> depth) * (Math.min(to, hi) - Math.max(from, low) + 1);
		}
		
		int root2 = root << 1;
		return calc(root2, depth - 1, from, to) + calc(root2 + 1, depth - 1, from, to);
	}
	
	/**
	 * Считает сумму элементов с <code>from</code> по <code>to</code> включительно.
	 */
	private int calc(int from, int to) {
		return calc(1, k, from + dx, to + dx);
	}

	private void solve() throws IOException {
		in = new BufferedReader(new FileReader(new File(problemName + ".in")));
		out = new PrintWriter(new File(problemName + ".out"));
		
		n = Integer.parseInt(in.readLine());
		k = 0;
		while ((1 << k) < n) {
			k++;
		}
		dx = 1 << k;
		a = new int[1 << (k + 1)];
		mark = new boolean[1 << (k + 1)];
		while (true) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			String action = st.nextToken();
			if (action.equals("set")) {
				int from = Integer.parseInt(st.nextToken());
				int to = Integer.parseInt(st.nextToken());
				int value = Integer.parseInt(st.nextToken());
				set(from, to, value);
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
		new Thread(new SegmentsTree2()).start();
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
