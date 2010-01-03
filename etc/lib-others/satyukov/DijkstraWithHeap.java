import java.io.*;
import java.util.*;

/**
 * Алгоритм Дейкстры с хипом (ориентированный граф, способ представления - список ребер).
 * Время работы O(ElogV).
 * 
 * @author Roman V Satyukov
 */
public class DijkstraWithHeap implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	private static final String problemName = "dijkstra";
	
	/**
	 * Граф.
	 * 
	 * @author Roman V Satyukov
	 */
	private class Graph {
		private int[] head;
		private int[] next;
		private int[] target;
		private int[] cost;
		private int[] dist;
		private int edgesNumber;
		public static final int inf = Integer.MAX_VALUE / 2 - 1;

		/**
		 * <code>heap</code> -- хип из номеров вершин. Ключ вершины <code>u</code> -- <code>dist[u]</code>.
		 * <code>pos[u]</code> -- позиция вершины <code>u</code> в хипе.
		 */
		private int[] heap;
		private int[] pos;
		private int heapSize;
		
		/**
		 * Меняет два элемента хипа местами.
		 */
		private void heapSwap(int u, int v) {
			int tmp = heap[u];
			heap[u] = heap[v];
			heap[v] = tmp;
			pos[heap[u]] = u;
			pos[heap[v]] = v;
		}

		/**
		 * "Просеивание вверх" хипа.
		 */
		private void siftUp(int u) {
			while (u > 0) {
				int parent = (u - 1) >> 1;
				if (dist[heap[parent]] > dist[heap[u]]) {
					heapSwap(u, parent);
					u = parent;
					continue;
				}
				break;
			}
		}

		/**
		 * "Просеивание вниз" хипа.
		 */
		private void siftDown(int u) {
			while (true) {
				int left = (u << 1) + 1;
				int right = left + 1;
				int min = u;
				if ((left < heapSize) && (dist[heap[left]] < dist[heap[min]])) {
					min = left;
				}
				if ((right < heapSize) && (dist[heap[right]] < dist[heap[min]])) {
					min = right;
				}
				if (min == u) {
					break;
				}
				heapSwap(u, min);
				u = min;
			}
		}

		/**
		 * Добавляет вершину в хип (расстояние до нее должно быть установлено в массиве <code>dist</code>).
		 */
		private void add2heap(int u) {
			heap[heapSize] = u;
			pos[u] = heapSize;
			heapSize++;
			siftUp(heapSize - 1);
		}
		
		/**
		 * Возвращает номер минимальной (в смысле расстояния в массиве <code>dist</code>) вершины в хипе.
		 */
		private int extractMin() {
			int result = heap[0];
			heap[0] = heap[heapSize - 1];
			pos[heap[0]] = 0;
			pos[result] = -1;
			heapSize--;
			siftDown(0);
			return result;
		}
		
		/**
		 * Создает пустой граф из максимум <code>n</code> вершин и максимум <code>m</code> ребер.
		 * 
		 * @param n Максимальное число вершин.
		 * @param m Максимальное число ребер.
		 */
		public Graph(int n, int m) {
			head = new int[n];
			next = new int[m];
			target = new int[m];
			cost = new int[m];
			Arrays.fill(head, -1);
			edgesNumber = 0;

			heap = new int[n];
			pos = new int[n];
			dist = new int[n];
		}

		/**
		 * Добавляет в граф ребро <code>u->v</code> длины <code>c</code>.
		 */
		public void addEdge(int u, int v, int c) {
			target[edgesNumber] = v;
			cost[edgesNumber] = c;
			next[edgesNumber] = head[u];
			head[u] = edgesNumber++;
		}
		
		/**
		 * Находит длины кратчайшин путей от вершины <code>source</code> до все других.
		 */
		public int[] dijkstra(int source) {
			Arrays.fill(dist, inf);
			dist[source] = 0;
			heapSize = 0;
			
			add2heap(source);
			while (heapSize > 0) {
				int u = extractMin();
				int cur = head[u];
				while (cur != -1) {
					int v = target[cur];
					if (dist[u] + cost[cur] < dist[v]) {
						if (dist[v] == inf) {
							dist[v] = dist[u] + cost[cur];
							add2heap(v);
						} else {
							dist[v] = dist[u] + cost[cur];
							siftUp(pos[v]);
						}
					}
					cur = next[cur];
				}
			}
			
			return dist.clone();
		}
	}

	public void run() {
		try {
			solve();
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
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
			int c = Integer.parseInt(st.nextToken());
			g.addEdge(u, v, c);
		}
		int source = Integer.parseInt(in.readLine()) - 1;
		int[] answer = g.dijkstra(source);
		for (int i = 0; i < n; i++) {
			if (answer[i] == Graph.inf) {
				out.print("+INF");
			} else {
				out.print(answer[i]);
			}
			if (i < n - 1) {
				out.print(" ");
			}
		}
		out.println();
		
		in.close();
		out.close();
	}

	public static void main(String[] args) {
		new Thread(new DijkstraWithHeap()).start();
	}
}
