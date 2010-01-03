#include <cstdio>
#include <cctype>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define INF 10000000

int N, deg[10010];
vector<int> adj[10010], adj_c[10010];

int dist[10010], loc[10010], heap[10010], heap_n;

void heapSwap(int i, int j)
{
	int t = heap[i];
	loc[heap[i] = heap[j]] = i;
	loc[heap[j] = t] = j;
}

void heapDown(int i)
{
	int j;
	while ((j = 2 * i) <= heap_n) {
		if (j + 1 <= heap_n && dist[heap[j+1]] < dist[heap[j]]) j++;
		if (dist[heap[i]] <= dist[heap[j]]) return;
		heapSwap(i, j);
		i = j;
	}
}

void heapUp(int i)
{
	for (; i > 1 && dist[heap[i]] < dist[heap[i/2]]; i /= 2)
		heapSwap(i, i/2);
}

int dijkstra(int source, int dest)
{
	for (int i = 1; i <= N; i++) dist[i] = INF;
	dist[source] = 0;

	heap_n = 1;
	heap[1] = source;

	for (int i = 1; i <= N; i++) loc[i] = -1;
	loc[source] = 1;

	while (heap_n > 0) {
		int x = heap[1];
		if (--heap_n != 0) {
			loc[heap[1] = heap[heap_n+1]] = 1;
			heapDown(1);
		}
		loc[x] = -1;

		if (x == dest) break;

		for (int i = 0; i < deg[x]; i++) {
			int y = adj[x][i];
			if (dist[x] + adj_c[x][i] < dist[y]) {
				if (loc[y] < 0) {
					heap[++heap_n] = y;
					loc[y] = heap_n;
				}

				dist[y] = dist[x] + adj_c[x][i];
				heapUp(loc[y]);
			}
		}
	}

	return dist[dest];
}

int main()
{
	int T;
	char buf1[256], buf2[256];
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);

		map<string, int> mp;
		for (int i = 1; i <= N; i++) {
			scanf(" %s %d", buf1, &deg[i]);
			mp[buf1] = i;

			adj[i].assign(deg[i], 0);
			adj_c[i].assign(deg[i], 0);
			for (int j = 0; j < deg[i]; j++) {
				scanf("%d %d", &adj[i][j], &adj_c[i][j]);
			}
		}

		int Q;
		scanf("%d", &Q);

		while (Q-- > 0 && scanf(" %s %s", buf1, buf2) == 2) {
			int s = mp[buf1];
			int t = mp[buf2];
			printf("%d\n", dijkstra(s, t));
		}
	}

	return 0;
}
