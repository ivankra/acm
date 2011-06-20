import java.io.*;
import java.util.*;

/**
 * Вычисление площади объединения N прямоугольников со сторонами параллельными осям координат.
 * Время работы: O(NlogN).
 * 
 * Во входном файле (rectangles.in) заданы N (N >= 1) прямоугольников.
 * Каждый прямоугольник задается 4 числами - координатами левого нижнего края (x1,y1)
 * и правого верхнего (x2, y2). Все координаты быть целыми числами, по модулю <= 10^9.
 * Все прямоугольники должны иметь ненулевую площадь.
 * В выходной файл выводится площадь объединения этих прямоугольников.
 * Пример:
 *   3
 *   0 0 3 2
 *   0 3 3 5
 *   1 1 2 4
 *  
 * Ответ: 13
 * 
 * @author Roman V Satyukov
 */
public class RectanglesUnionArea implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	private static final String problemName = "rectangles";
	
	// Прямоугольник: (x1,y1) - левый нижний угол, (x2,y2) - правый верхний
	private class Rectangle {
		public int x1, y1, x2, y2;
		
		public Rectangle(String line) {
			StringTokenizer st = new StringTokenizer(line);
			x1 = Integer.parseInt(st.nextToken());
			y1 = Integer.parseInt(st.nextToken());
			x2 = Integer.parseInt(st.nextToken());
			y2 = Integer.parseInt(st.nextToken());
		}
	}
	
	// События для движущейся прямой:
	// x: x-координата
	// rect: номер прямоугольника
	// remove: добавить или удалить отрезок
	private class Event implements Comparable<Event>{
		public int x;
		public int rect;
		public boolean remove;
		
		public Event(int x, int rect, boolean remove) {
			this.x = x;
			this.rect = rect;
			this.remove = remove;
		}
		
		public int compareTo(Event that) {
			if (this.x - that.x != 0) {
				return this.x - that.x;
			} else {
				return this.rect - that.rect;
			}
		}
	}
	
	// Дерево отрезков
	private class SegmentsTree {
		private int[] x;
		private int[] y;
		private int[] count;
		private int dx;
		private int n;
		
		public SegmentsTree(int n, int[] yCoords) {
			dx = 1;
			this.n = 0;
			while (dx < n) {
				dx = dx << 1;
				this.n++;
			}
			x = new int[2 * dx];
			y = new int[dx];
			for (int i = 0; i < yCoords.length; i++) {
				y[i] = yCoords[i];
			}
			for (int i = yCoords.length; i < dx; i++) {
				y[i] = yCoords[yCoords.length - 1];
			}
			
			count = new int[2 * dx];
		}

		private int cover(int u, int depth) {
			int from = u << depth;
			int to = ((u + 1) << depth) - 1;
			return (count[u] > 0) ? y[to + 1 - dx] - y[from - dx] : x[u];
		}

		private void add(int u, int depth, int from, int to) {
			int low = u << depth;
			int hi = ((u + 1) << depth) - 1;
			if (to < low || from > hi) {
				return;
			}
			if (from <= low && hi <= to) {
				count[u]++;
				return;
			}
			add(2 * u, depth - 1, from, to);
			add(2 * u + 1, depth - 1, from, to);
			x[u] = cover(2 * u, depth - 1) + cover(2 * u + 1, depth - 1);
		}

		private void remove(int u, int depth, int from, int to) {
			int low = u << depth;
			int hi = ((u + 1) << depth) - 1;
			if (to < low || from > hi) {
				return;
			}
			if (from <= low && hi <= to) {
				count[u]--;
				return;
			}
			remove(2 * u, depth - 1, from, to);
			remove(2 * u + 1, depth - 1, from, to);
			x[u] = cover(2 * u, depth - 1) + cover(2 * u + 1, depth - 1);
		}

		public int calc() {
			return cover(1, n);
		}

		public void add(int u, int v) {
			u += dx;
			v += dx;
			add(1, n, u, v);
		}
		
		public void remove(int u, int v) {
			u += dx;
			v += dx;
			remove(1, n, u, v);
		}
	}
	
	private void solve() throws IOException {
		in = new BufferedReader(new FileReader(new File(problemName + ".in")));
		out = new PrintWriter(new File(problemName + ".out"));
		
		// Чтение
		int n = Integer.parseInt(in.readLine());
		Rectangle[] rectrangles = new Rectangle[n];
		for (int i = 0; i < n; i++) {
			rectrangles[i] = new Rectangle(in.readLine());
		}
		
		// Наложение сетки: перенумерация y-координат
		int[] yCoords = new int[2 * n];
		for (int i = 0; i < n; i++) {
			yCoords[i] = rectrangles[i].y1;
			yCoords[i + n] = rectrangles[i].y2;
		}
		Arrays.sort(yCoords);
		for (int i = 0; i < n; i++) {
			rectrangles[i].y1 = Arrays.binarySearch(yCoords, rectrangles[i].y1);
			rectrangles[i].y2 = Arrays.binarySearch(yCoords, rectrangles[i].y2);
		}
		
		// Создание событий - когда на движущейся прямой что-то меняется
		Event[] events = new Event[2 * n];
		for (int i = 0; i < n; i++) {
			events[i] = new Event(rectrangles[i].x1, i, false);
			events[i + n] = new Event(rectrangles[i].x2, i, true);
		}
		Arrays.sort(events);
		
		// Создание дерева отрезков
		SegmentsTree tree = new SegmentsTree(2 * n, yCoords);
		
		// Обработка событий
		long area = 0;
		for (int i = 0; i < events.length; i++) {
			Event cur = events[i];
			int rect = cur.rect;
			long dx = (i > 0) ? events[i].x - events[i - 1].x : 0;
			if (dx > 0) {
				area = area + dx * tree.calc();
			}
			if (!cur.remove) {
				tree.add(rectrangles[rect].y1, rectrangles[rect].y2 - 1);
			} else {
				tree.remove(rectrangles[rect].y1, rectrangles[rect].y2 - 1);
			}
		}
		out.println(area);
		
		in.close();
		out.close();
	}

	public static void main(String[] args) {
		new Thread(new RectanglesUnionArea()).start();
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
