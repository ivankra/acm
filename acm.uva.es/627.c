#include <stdio.h>
#include <string.h>
#include <ctype.h>

int adj[512][512];
int idlist[512], n;

void find(int x, int y)
{
	static int v[512], p[512], q[512], h, t;
	int i, k;

	memset(v, 0, sizeof(v));
	for (h = 0, t = 1, q[0] = y, v[y] = 1; h < t;) {
		for (k = q[h++], i = 0; i < n; i++) {
			if (adj[i][k] && !v[i]) {
				v[i] = 1;
				p[i] = k;
				q[t++] = i;
			}
		}
	}

	if (v[x] == 0) {
		printf("connection impossible\n");
		return;
	}

	for (; x != y; x = p[x])
		printf("%d ", idlist[x]);
	printf("%d\n", idlist[y]);
}

int map(int id)
{
	int i;

	for (i = 0; i < n; i++)
		if (idlist[i] == id) return i;

	idlist[n] = id;
	return n++;
}

int main()
{
	int i, c, m, x, y, r;

	while (scanf("%d", &r) == 1) {
		printf("-----\n");

		memset(adj, 0, sizeof(adj));
		for (n = 0, i = 0; i < r && scanf("%d-", &x) == 1; i++) {
			x = map(x);
			for (;;) {
				while ((c = getchar()) != EOF)
					if (c == '\n' || isdigit(c)) break;
				if (c == '\n' || c == EOF) break;

				ungetc(c, stdin);
				scanf("%d", &y);

				adj[x][map(y)] = 1;
			}
		}

		for (scanf("%d", &m); m-- > 0 && scanf("%d %d", &x, &y) == 2;)
			find(map(x), map(y));
	}

	return 0;
}
