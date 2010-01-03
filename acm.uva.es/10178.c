#include <stdio.h>
#include <string.h>

int adj[64][64], map[256];

void dfs(int x)
{
	static int s[64], v[64];
	int i, t;

	memset(v, 0, sizeof(v));
	v[x] = 1;

	for (s[0] = x, t = 1; t > 0;) {
		x = s[--t];
		adj[x][x] = 0;
		for (i = 0; i < 64; i++)
			if (adj[x][i] && !v[i]) v[s[t++] = i] = 1;
	}
}

int main()
{
	static char s1, s2;
	int v, e, c, i, x, y;

	for (i = 0; i < 26; i++)
		map['A' + i] = i;

	for (i = 0; i < 26; i++)
		map['a' + i] = i + 26;

	while (scanf("%d %d", &v, &e) == 2) {
		memset(adj, 0, sizeof(adj));

		for (i = 0, c = v; i < e && scanf(" %c %c", &s1, &s2) == 2; i++) {
			x = map[(int)s1];
			y = map[(int)s2];

			if (adj[x][x]++ == 0)
				c--;

			if (adj[y][y]++ == 0)
				c--;

			adj[x][y] = adj[y][x] = 1;
		}

		for (i = 0; i < 64; i++)
			if (adj[i][i]) c++, dfs(i);

		printf("%d\n", e - v + c + 1);
	}

	return 0;
}
