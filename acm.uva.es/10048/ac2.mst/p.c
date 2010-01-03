#include <stdio.h>

#define MAXN	128
#define MAXM	1024
#define NRCELLS	4096
#define INF	0x3FFFFFFF

#define max(a, b) (((a) > (b)) ? (a) : (b))

int cval[NRCELLS], caux[NRCELLS], cnext[NRCELLS], cfree;
int mstadj[MAXN], adj[MAXN], mstroot[MAXN], n;

static int insert(int list, int val, int aux)
{
	int t;

	t = cfree;
	cfree = cnext[cfree];

	cval[t] = val;
	caux[t] = aux;
	cnext[t] = list;

	return t;
}

static void release(int list)
{
	int t;

	while (list != 0) {
		t = cnext[list];
		cnext[list] = cfree;
		cfree = list;
		list = t;
	}
}

static void prim(int root)
{
	static int dist[MAXN], pred[MAXN];
	int i, k;

	for (i = root; i <= n; i++)
		dist[i] = INF;

	for (i = adj[root]; i != 0; i = cnext[i]) {
		dist[cval[i]] = caux[i];
		pred[cval[i]] = root;
	}
	mstroot[root] = root;

	for (;;) {
		for (k = -1, i = root + 1; i <= n; i++) {
			if (dist[i] == INF || mstadj[i] != 0) continue;
			if (k < 0 || dist[i] < dist[k]) k = i;
		}

		if (k < 0)
			break;

		mstadj[pred[k]] = insert(mstadj[pred[k]], k, dist[k]);
		mstadj[k] = insert(mstadj[k], pred[k], dist[k]);
		mstroot[k] = root;

		for (i = adj[k]; i != 0; i = cnext[i]) {
			if (dist[cval[i]] > caux[i]) {
				dist[cval[i]] = caux[i];
				pred[cval[i]] = k;
			}
		}
	}
}

static int search(int x, int y)
{
	static int st[MAXN], dist[MAXN], pred[MAXN];
	int i, top;

	if (x == y)
		return 0;

	top = 1;
	st[0] = x;
	dist[x] = 0;
	pred[x] = x;

	while (top > 0) {
		x = st[--top];

		for (i = mstadj[x]; i != 0; i = cnext[i]) {
			if (cval[i] == pred[x]) continue;

			dist[cval[i]] = max(dist[x], caux[i]);

			if (cval[i] == y)
				return dist[cval[i]];

			st[top++] = cval[i];
			pred[cval[i]] = x;
		}
	}

	return 0;
}

int main()
{
	int i, m, q, t, x, y, z;

	for (cfree = 1, i = 1; i < NRCELLS; i++)
		cnext[i] = i + 1;
	cnext[NRCELLS - 1] = 0;

	for (i = 0; i < MAXN; i++)
		mstadj[i] = adj[i] = 0;

	for (t = 1; scanf("%d %d %d", &n, &m, &q) == 3 && n > 0; t++) {
		while (m-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3) {
			adj[x] = insert(adj[x], y, z);
			adj[y] = insert(adj[y], x, z);
		}

		for (i = 1; i <= n; i++)
			if (mstadj[i] == 0) prim(i);

		printf("%sCase #%d\n", (t == 1) ? "" : "\n", t);

		while (q-- > 0 && scanf("%d %d", &x, &y) == 2) {
			if (mstroot[x] != mstroot[y])
				printf("no path\n");
			else
				printf("%d\n", search(x, y));
		}

		for (i = 1; i <= n; i++) {
			release(adj[i]);
			release(mstadj[i]);
			mstadj[i] = adj[i] = 0;
		}
	}

	return 0;
}
