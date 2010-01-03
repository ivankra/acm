#include <stdio.h>
#include <string.h>

int adj[256][256], n, nc;
char name[256][32];

int find(int x, int y)
{
	static int v[256], d[256];
	int i, k;

	memset(v, 0, sizeof(v));
	memset(d, 0, sizeof(d));

	for (d[x] = 10000;;) {
		for (k = 0; k < n && v[k]; k++);

		if (k >= n)
			break;

		for (i = k + 1; i < n; i++)
			if (v[i] == 0 && d[i] > d[k]) k = i;

		for (v[k] = 1, i = 0; i < n; i++) {
			if (d[i] < d[k] && d[i] < adj[k][i])
				d[i] = (adj[k][i] < d[k]) ? adj[k][i] : d[k];
		}
	}

	return d[y];
}

int get(char *s)
{
	int i;

	for (i = 0; i < nc; i++)
		if (strcmp(name[i], s) == 0) return i;

	strcpy(name[nc], s);
	return nc++;
}

int main()
{
	char s1[256], s2[256];
	int i, j, m, t, w;

	for (t = 1; scanf("%d %d", &n, &m) == 2 && n > 0; t++) {
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				adj[i][j] = 0;

		for (nc = 0; m-- > 0 && scanf(" %s %s %d", s1, s2, &w) == 3;)
			if (adj[i = get(s1)][j = get(s2)] < w)
				adj[i][j] = adj[j][i] = w;

		scanf(" %s %s", s1, s2);
		printf("Scenario #%d\n%d tons\n\n", t, find(get(s1), get(s2)));
	}

	return 0;
}
