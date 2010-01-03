#include <stdio.h>
#include <string.h>

#define MAXC 65536
#define MAXN 8192

int ref[MAXC], prev[MAXC], next[MAXC], adj[MAXN], freelist, nvert;

void insert(int *p, int r)
{
	int q = freelist;
	freelist = next[q];
	ref[q] = r;
	next[q] = *p;
	prev[*p] = q;
	prev[q] = 0;
	(*p) = q;
}

void release(int *a)
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

int augment(int src)
{
	static int q[MAXN], p[MAXN], e[MAXN];
	int i, j, h, t;

	for (i = 0; i <= nvert; i++)
		p[i] = 0;

	/* BFS to find augmenting path to the sink */
	for (p[q[h = 0] = src] = src, t = 1; h < t && p[1] == 0;) {
		for (j = adj[i = q[h++]]; j != 0; j = next[j]) {
			if (p[ref[j]] == 0) {
				p[ref[j]] = i;
				e[ref[j]] = j;
				q[t++] = ref[j];
			}
		}
	}

	if (p[1] == 0)
		return 0;

	/* augment along the found path, by changing direction of the edges */
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
	static int x[8192], y[8192], v_in[64][64], v_out[64][64];
	int i, j, p, s, a, b;

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

		for (i = 1; i <= nvert; i++)
			release(&adj[i]);
	}

	return 0;
}
