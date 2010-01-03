#include <cstdio>

#define INF 0x3FFFFFFF

int next[150000], what[150000], cost[150000], dist[65536], last;
int heap[65536], loc[65536], heapn;

void up(int x) {
	int p;
	for (p = loc[x]; p > 1 && dist[heap[p >> 1]] > dist[x]; p >>= 1)
		loc[heap[p] = heap[p >> 1]] = p;
	loc[heap[p] = x] = p;
}

int get() {
	int i, j, p, r;

	r = heap[1];
	loc[r] = -1;
	heapn--;

	if (heapn <= 0) return r;

	loc[heap[1] = heap[heapn + 1]] = 1;

	for (p = 1; (j = (p << 1)) <= heapn; p = i) {
		i = (dist[heap[j]] < dist[heap[p]]) ? j : p;
		j++;
		if (j <= heapn && (dist[heap[j]] < dist[heap[i]])) i = j;
		if (i == p) break;
		j = heap[p];
		loc[heap[p] = heap[i]] = p;
		loc[heap[i] = j] = i;
	}

	return r;
}

void edge(int x, int y, int z) {
	last++;
	what[last] = y;
	cost[last] = z;
	next[last] = next[x];
	next[x] = last;
}

int main()
{
	int cs=1, T, i, n, m, x, y, z, src, dst;
	scanf("%d", &T);

	for (cs = 1; cs <= T; cs++) {
		scanf("%d %d %d %d", &n, &m, &src, &dst);
		for (i = 0; i <= n; i++) next[i] = 0;

		for (last = n; m-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3;) {
			if (x == y) continue;
			edge(x, y, z);
			edge(y, x, z);
		}

		for (i = 0; i <= n; i++)
			dist[i] = INF, loc[i] = 0;
		loc[heap[heapn = 1] = src] = 1;
		dist[src] = 0;

		while (heapn >= 1) {
			x = get();
			if (x == dst) break;
			for (i = next[x]; i != 0; i = next[i]) {
				y = what[i];
				if (dist[y] == INF) {
					heapn++;
					loc[heap[heapn] = y] = heapn;
				} else {
					if (loc[y] < 0) continue;
					z = dist[x] + cost[i];
					if (z >= dist[y]) continue;
				}
				dist[y] = dist[x] + cost[i];
				up(y);
			}
		}

		printf("Case #%d: ", cs);
		if (dist[dst] < INF) printf("%d\n", dist[dst]);
		else printf("unreachable\n");
	}

	return 0;
}
