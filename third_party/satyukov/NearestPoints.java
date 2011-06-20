import java.io.*;
import java.util.*;

/**
 * Алгоритм поиска двух ближайших точек на плоскости.
 * Время работы: O(NlogN), где N - число точек.
 * Пример входного файла (nearest.in):
 *   6
 *   0 10
 *   4 4
 *   10 10
 *   10 0
 *   5 5
 *   0 0
 * 
 * @author Roman V Satyukov
 */
public class NearestPoints implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	private static final String problemName = "nearest";
	private Point[] points, tmpPoints;
	private Point p1, p2;
	
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
			return this.x - that.x;
		}
		
		public int distanceTo(Point that) {
			return (this.x - that.x) * (this.x - that.x) + (this.y - that.y) * (this.y - that.y);
		}
		
		@Override
		public String toString() {
			return n + " (" + x + " " + y + ")";
		}
	}

	/**
	 * Сортирует массив <code>points</code> по Y-координате.
	 * Возвращает две ближайшие точки в глобальных переменных <code>p1</code> и <code>p2</code>.
	 */
	private void merge(int low, int hi) {
		if (low == hi) {
			p1 = null;
			p2 = null;
			return;
		}
		int middle = (low + hi) / 2;
		int middleX = points[middle].x;
		Point ans1, ans2;
		merge(low, middle);
		ans1 = p1;
		ans2 = p2;
		int dist1 = ((p1 != null) && (p2 != null)) ? p1.distanceTo(p2) : Integer.MAX_VALUE;
		merge(middle + 1, hi);
		int minDist = ((p1 != null) && (p2 != null)) ? p1.distanceTo(p2) : Integer.MAX_VALUE;
		if (dist1 < minDist) {
			p1 = ans1;
			p2 = ans2;
			minDist = dist1;
		}
		int a = low;
		int b = middle + 1;
		int c = low;
		while ((a <= middle) && (b <= hi)) {
			if (points[a].y <= points[b].y) {
				tmpPoints[c++] = points[a++];
			} else {
				tmpPoints[c++] = points[b++];
			}
		}
		while (a <= middle) {
			tmpPoints[c++] = points[a++];
		}
		while (b <= hi) {
			tmpPoints[c++] = points[b++];
		}
		
		// Фильтруем точки достаточно близкие к границе
		c = low;
		for (int i = low; i <= hi; i++) {
			if ((tmpPoints[i].x - middleX) * (tmpPoints[i].x - middleX) > minDist) {
				continue;
			}
			
			points[c++] = tmpPoints[i];
		}
		// Ищем две ближайшие точки около границы
		for (int i = low; i < c; i++) {
			for (int j = i + 1; (j <= i + 7) && (j < c); j++) {
				int tmp = points[i].distanceTo(points[j]);
				if (tmp < minDist) {
					minDist = tmp;
					p1 = points[i];
					p2 = points[j];
				}
			}
		}
		
		for (int i = low; i <= hi; i++) {
			points[i] = tmpPoints[i];
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
		
		Arrays.sort(points);
		tmpPoints = new Point[n];
		merge(0, n - 1);
		out.println("Min distance = " + Math.hypot(p1.x - p2.x, p1.y - p2.y));
		out.println("  p1 = " + p1);
		out.println("  p2 = " + p2);
		
		in.close();
		out.close();
	}

	public static void main(String[] args) {
		new Thread(new NearestPoints()).start();
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
