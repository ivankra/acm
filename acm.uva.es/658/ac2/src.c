#include <stdio.h>
#include <stdlib.h>

int read(int, char *, int);

char inbuf[1048576], *inp;
int isdig[256], dist[1048576], rank[1048576], heap[1048580], heap_n;
int n, m, all;

#define READ(x) \
       { while (!isdig[*inp]) inp++; \
         for (x = *inp++ - '0'; isdig[*inp];) x = x * 10 + *inp++ - '0'; }

struct {
	int bplus, bminus, fplus, fminus, c_fminus, tm;
	int bmask, bneed;
} patch[128];

static void heap_up(int p)
{
	int t;

	for (t = heap[p]; p > 1 && dist[heap[p >> 1]] > dist[t]; p >>= 1) {
		heap[p] = heap[p >> 1];
		rank[heap[p]] = p;
	}

	heap[p] = t;
	rank[t] = p;
}

static void heap_down(int p)
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

static void heap_add(int t)
{
	heap[rank[t] = ++heap_n] = t;
	heap_up(heap_n);
}

static int heap_get()
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

static void take(int *p, int *m)
{
	int i, c;

	for (i = n - 1, *p = *m = 0; i >= 0 && *inp; inp++) {
		if (*inp == '0')
			i--;
		else if (*inp == '+')
			*p |= 1 << i--;
		else if (*inp == '-')
			*m |= 1 << i--;
	}
}

static int solve()
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

void main2()
{
	int i, t;

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = '\0';

	for (i = 0; i < 256; i++)
		isdig[i] = ('0' <= i && i <= '9');

	for (t = 1;; t++) {
		READ(n);
		if (n == 0) break;

		READ(m);

		all = (1 << n) - 1;
		for (i = 0; i < m; i++) {
			READ(patch[i].tm);

			take(&patch[i].bplus, &patch[i].bminus);
			patch[i].bmask = patch[i].bplus | patch[i].bminus;
			patch[i].bneed = patch[i].bplus;

			take(&patch[i].fplus, &patch[i].fminus);
			patch[i].c_fminus = patch[i].fminus ^ all;
		}

		printf("Product %d\n", t);

		if ((i = solve()) < 0)
			printf("Bugs cannot be fixed.\n\n");
		else
			printf("Fastest sequence takes %d seconds.\n\n", i);
	}

	exit(0);
}

int main()
{
	main2();
	return 0;
}
