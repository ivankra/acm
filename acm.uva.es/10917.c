#include <stdio.h>
#include <assert.h>

#define INF 0x7FFFFFFF

int next[524288], what[524288], cost[524288], dist[1024], tab[1024], last;
int heap[1024], loc[1024], heapn;

void up(int x)
{
	int p;
	for (p = loc[x]; p > 1 && dist[heap[p >> 1]] > dist[x]; p >>= 1)
		loc[heap[p] = heap[p >> 1]] = p;
	loc[heap[p] = x] = p;
}

int get()
{
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

void edge(int x, int y, int z)
{
	last++;
	what[last] = y;
	cost[last] = z;
	next[last] = next[x];
	next[x] = last;
}

int f(int x)
{
	int i;

	if (tab[x] >= 0) return tab[x];

	for (tab[x] = 0, i = next[x]; i != 0; i = next[i])
		if (dist[what[i]] < dist[x]) tab[x] += f(what[i]);
	return tab[x];
}

int main()
{
	int i, n, m, x, y, z;

	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		for (i = 0; i <= n; i++)
			next[i] = 0;

		for (last = n; m-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3;) {
			if (x == y) continue;
			assert(1 <= x && x <= n && 1 <= y && y <= n && 0 <= z);
			edge(x, y, z);
			edge(y, x, z);
		}

		for (i = 0; i <= n; i++)
			dist[i] = INF, loc[i] = 0, tab[i] = -1;
		loc[heap[heapn = 1] = 2] = 1;
		dist[2] = 0;

		while (heapn >= 1) {
			x = get();
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

		tab[2] = 1;
		printf("%d\n", f(1));
	}

	return 0;
}
