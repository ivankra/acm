import java.io.*;
import java.util.*;

/**
 * Алгоритм Грэхама поиска выпуклой оболочки (Время работы: O(NlogN))
 * Во входном файле (convex.in) заданы N (N >= 2) различных точек.
 * Координаты всех точек быть целыми числами, по модулю <= 10000.
 * В выходной файл выводится выпуклая оболочка этих точек.
 * Пример:
 *   9
 *   4 6
 *   -1 3
 *   6 4
 *   2 5
 *   5 5
 *   5 2
 *   7 3
 *   3 1
 *   1 2
 * 
 * @author Roman V Satyukov
 */
public class ConvexHull implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	private static final String problemName = "convex";
	private Point[] points;
	
	private class Point implements Comparable<Point>{
		// n    - номер точки во входном файле
		// x, y - координаты точки
		public int x, y, n;
		
		public Point(int x, int y, int n) {
			this.x = x;
			this.y = y;
			this.n = n;
		}

		public int compareTo(Point that) {
			int dx1 = this.x - points[0].x; 
			int dy1 = this.y - points[0].y; 
			int dx2 = that.x - points[0].x; 
			int dy2 = that.y - points[0].y;
			int vp = dx1 * dy2 - dx2 * dy1;
			if (vp != 0) {
				return -vp;
			}
			int dist1 = dx1 * dx1 + dy1 * dy1;
			int dist2 = dx2 * dx2 + dy2 * dy2;
			return dist1 - dist2;
		}
		
		@Override
		public String toString() {
			return n + " (" + x + " " + y + ")";
		}
	}

	private void solve() throws IOException {
		in = new BufferedReader(new FileReader(new File(problemName + ".in")));
		out = new PrintWriter(new File(problemName + ".out"));
		
		int n = Integer.parseInt(in.readLine());
		points = new Point[n];
		for (int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			points[i] = new Point(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), i + 1);
		}
		int min = 0;
		for (int i = 0; i < n; i++) {
			if (points[i].x < points[min].x || (points[i].x == points[min].x) && (points[i].y < points[min].y)) {
				min = i;
			}
		}
		Point tmp = points[0];
		points[0] = points[min];
		points[min] = tmp;
		Arrays.sort(points, 1, n);
		Point[] stack = new Point[n];
		stack[0] = points[0];
		stack[1] = points[1];
		int sp = 2;
		for (int i = 2; i < n; i++) {
			while (sp >= 2) {
				int dx1 = stack[sp - 1].x - stack[sp - 2].x;
				int dy1 = stack[sp - 1].y - stack[sp - 2].y;
				int dx2 = points[i].x - stack[sp - 2].x;
				int dy2 = points[i].y - stack[sp - 2].y;
				int vp = dx1 * dy2 - dx2 * dy1;
				if (vp > 0) {
					break;
				}
				sp--;
			}
			stack[sp++] = points[i];
		}
		out.println(sp);
		for (int i = 0; i < sp; i++) {
			out.println(stack[i]);
		}
		
		in.close();
		out.close();
	}

	public static void main(String[] args) {
		new Thread(new ConvexHull()).start();
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
