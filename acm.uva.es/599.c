#include <stdio.h>
#include <string.h>
#include <ctype.h>

int adj[32][32], c[32], q[32];

int dfs(int v)
{
	int i, t, r;

	for (c[q[0] = v] = 1, t = 1, r = 0; t > 0;)
		for (v = q[--t], i = 0; i < 26; i++)
			if (adj[v][i] && !c[i]) c[q[t++] = i] = r = 1;
	return r;
}

int main()
{
	char s[1024], x[16], y[16], *p;
	int i, j, t, r[2];

	for (scanf("%d", &t); t-- > 0;) {
		memset(adj, 0, sizeof(adj));

		while (scanf(" %[^\n]\n", s) == 1 && s[0] != '*') {
			sscanf(s, " ( %c , %c )", x, y);
			i = toupper(x[0]) - 'A';
			j = toupper(y[0]) - 'A';
			adj[i][j] = adj[j][i] = 1;
		}

		memset(c, 0, sizeof(c));
		for (gets(p = s), r[0] = r[1] = 0; *p; p++)
			if (isalpha(*p) && c[i = toupper(*p) - 'A'] == 0)
				r[dfs(i)]++;

		printf("There are %d tree(s) and %d acorn(s).\n", r[1], r[0]);
	}

	return 0;
}
