#include <stdio.h>
#include <string.h>

#define MAXC 16384
#define MAXN 8192

static int ref[MAXC], prev[MAXC], next[MAXC], adj[MAXN], freelist, nvert;

static void insert(int *p, int r)
{
	register int q = freelist;
	freelist = next[q];
	ref[q] = r;
	next[q] = *p;
	prev[*p] = q;
	prev[q] = 0;
	(*p) = q;
}

static void release(int *a)
{
	int p, q;

	for (p = *a; p != 0;) {
		q = next[p];
		next[p] = freelist;
		freelist = p;
		p = q;
	}

	*a = 0;
}

static int augment(int src)
{
	static int q[MAXN], p[MAXN], e[MAXN];
	int i, j, k, t;

	for (i = 0; i <= nvert; i++)
		p[i] = 0;

	for (p[q[0] = src] = src, t = 1; t > 0;) {
		for (j = adj[i = q[--t]]; j != 0; j = next[j]) {
			if (p[k = ref[j]] == 0) {
				p[k] = i;
				e[k] = j;
				q[t++] = k;
				if (k == 1) goto found;
			}
		}
	}

	return 0;

found:

	for (i = 1; i != src; i = p[i]) {
		j = e[i];
		next[prev[j]] = next[j];
		prev[next[j]] = prev[j];
		if (j == adj[p[i]])
			adj[p[i]] = next[j];

		next[j] = freelist;
		freelist = j;

		insert(&adj[i], p[i]);
	}

	return 1;
}

int main()
{
	static int x[4096], y[4096], v_in[64][64], v_out[64][64], p, b;
	int i, j, s, a;

	for (freelist = i = 1; i < MAXC; i++)
		next[i] = i + 1;

	memset(adj, 0, sizeof(adj));

	scanf("%d", &p);
	while (p-- > 0 && scanf("%d %d %d", &s, &a, &b) == 3) {
		for (i = 0; i < b; i++)
			scanf("%d %d", &x[i], &y[i]);

		if (s <= 1 || a <= 1) {
			printf("possible\n");
			continue;
		}

		if (b > ((s + a) * 2 - 4)) {
			printf("not possible\n");
			continue;
		}

		/* label vertices */
		for (nvert = 1, i = 1; i <= s; i++) {
			for (j = 1; j <= a; j++) {
				v_in[i][j] = ++nvert;
				v_out[i][j] = ++nvert;
			}
			v_in[i][0] = v_in[i][a + 1] = 1;
		}

		for (i = 0; i <= (a+1); i++)
			v_in[0][i] = v_in[s + 1][i] = 1;

		/* make adjacency lists */
		for (i = 1; i <= s; i++) {
			for (j = 1; j <= a; j++) {
				insert(&adj[v_in[i][j]], v_out[i][j]);
				insert(&adj[v_out[i][j]], v_in[i][j - 1]);
				insert(&adj[v_out[i][j]], v_in[i][j + 1]);
				insert(&adj[v_out[i][j]], v_in[i - 1][j]);
				insert(&adj[v_out[i][j]], v_in[i + 1][j]);
			}
		}

		/* find augmenting paths from every bank's location
		   to the border (vertex 1) */
		for (i = 0; i < b; i++) {
			if (x[i] < 1 || x[i] > s || y[i] < 1 || y[i] > a)
				break;

			if (augment(v_in[x[i]][y[i]]) == 0)
				break;
		}

		printf((i < b) ? "not possible\n" : "possible\n");

		if (p == 0) break;

		for (i = 1; i <= nvert; i++)
			release(&adj[i]);
	}

	return 0;
}
