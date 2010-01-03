// Dijkstra
#include <cstdio>
#include <cstdlib>

int dist[1048576], rank[1048576], heap[1048580], heap_n;
int n, m, all;

struct {
	int bplus, bminus, fplus, fminus, c_fminus, tm;
	int bmask, bneed;
} patch[128];

void heap_up(int p)
{
	int t;
	for (t = heap[p]; p > 1 && dist[heap[p >> 1]] > dist[t]; p >>= 1) {
		heap[p] = heap[p >> 1];
		rank[heap[p]] = p;
	}
	heap[p] = t;
	rank[t] = p;
}

void heap_down(int p)
{
	int i, j, t;

	while ((j = (p << 1)) <= heap_n) {
		i = (dist[heap[j]] < dist[heap[p]]) ? j : p;

		if (++j <= heap_n && dist[heap[j]] < dist[heap[i]])
			i = j;

		if (i == p)
			break;

		t = heap[p];
		rank[heap[p] = heap[i]] = p;
		heap[p = i] = t;
	}

	rank[heap[p]] = p;
}

void heap_add(int t)
{
	heap[rank[t] = ++heap_n] = t;
	heap_up(heap_n);
}

int heap_get()
{
	int r;

	if (heap_n < 1)
		return -1;

	r = heap[1];

	if (heap_n == 1) {
		heap_n = 0;
	} else {
		heap[1] = heap[heap_n--];
		rank[heap[1]] = 1;
		heap_down(1);
	}

	rank[r] = -1;
	return r;
}

void take(int *p, int *m)
{
	int i, c;

	for (i = n - 1, *p = *m = 0; i >= 0 && (c = getchar()) != EOF;) {
		if (c == '0')
			i--;
		else if (c == '+')
			*p |= 1 << i--;
		else if (c == '-')
			*m |= 1 << i--;
	}
}

int solve()
{
	int i, j, k;

	for (i = 0; i <= all; i++)
		dist[i] = 0x7FFFFFFF;

	for (i = 0; i <= all; i++)
		rank[i] = 0;

	heap_n = 0;

	dist[all] = 0;
	heap_add(all);

	while ((k = heap_get()) > 0) {
		for (i = 0; i < m; i++) {
			if ((k & patch[i].bmask) != patch[i].bneed)
				continue;

			j = (k | patch[i].fplus) & patch[i].c_fminus;

			if (dist[j] <= (dist[k] + patch[i].tm))
				continue;

			dist[j] = dist[k] + patch[i].tm;

			if (rank[j] == 0)
				heap_add(j);
			else if (rank[j] > 0)
				heap_up(rank[j]);
		}
	}

	return ((k == 0) ? dist[0] : -1);
}

int main()
{
	scanf("%d %d", &n, &m);
	all = (1 << n) - 1;
	for (int i = 0; i < m && scanf("%d", &patch[i].tm) == 1; i++) {
		take(&patch[i].bplus, &patch[i].bminus);
		patch[i].bmask = patch[i].bplus | patch[i].bminus;
		patch[i].bneed = patch[i].bplus;

		take(&patch[i].fplus, &patch[i].fminus);
		patch[i].c_fminus = patch[i].fminus ^ all;
	}

	int r = solve();
	if (r < 0)
		printf("Bugs cannot be fixed.\n");
	else
		printf("Fastest sequence takes %d seconds.\n", r);
	return 0;
}
