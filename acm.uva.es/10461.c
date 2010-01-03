#include <stdio.h>
#include <string.h>

#define MAXM 8192

int adj[512], closure[512][512], tm[512], tab[512], n;
int ref[MAXM], next[MAXM], freelist;

void dfs(int s)
{
	static int st[1024];
	int i, *p;

	for (st[0] = s, p = st + 1; p > st;) {
		for (i = adj[*--p]; i != 0; i = next[i]) {
			if (closure[s][ref[i]] == 0) {
				closure[s][ref[i]] = 1;
				*p++ = ref[i];
			}
		}
	}
}

int insert(int p, int r)
{
	int t;
	t = freelist;
	freelist = next[freelist];
	next[t] = p;
	ref[t] = r;
	return t;
}

void release(int p)
{
	int q;
	while (p) {
		q = next[p];
		next[p] = freelist;
		freelist = p;
		p = q;
	}
}

int get(int s)
{
	int i, d;

	if (tab[s] >= 0)
		return tab[s];

	for (d = 0, i = 1; i <= n; i++)
		if (i != s && closure[i][s] == 0 && closure[s][i] == 0)
			d += tm[i];

	return (tab[s] = d);
}

int main()
{
	int i, m, t, x, y;

	for (freelist = i = 1; i < MAXM; i++)
		next[i] = i + 1;
	next[MAXM - 1] = 0;

	for (t = 1; scanf("%d %d", &n, &m) == 2 && n > 0; t++) {
		memset(closure, 0, sizeof(closure));
		memset(adj, 0, sizeof(adj));
		for (i = 1; i <= n; i++)
			tab[i] = -1;

		for (i = 1; i <= n; i++)
			scanf("%d", &tm[i]);

		while (m-- > 0 && scanf("%d %d", &x, &y) == 2)
			adj[y] = insert(adj[y], x);

		for (i = 1; i <= n; i++)
			dfs(i);

		printf("Case #%d:\n", t);
		for (scanf("%d", &m); m-- > 0 && scanf("%d", &x) == 1;)
			printf("%d\n", get(x));
		printf("\n");

		for (i = 1; i <= n; i++)
			release(adj[i]);
	}

	return 0;
}
