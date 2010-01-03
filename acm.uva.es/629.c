#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int adj[16][16], n;
int sets[1024], nsets;

int cmp(const void *p, const void *q)
{
	int a = *(int *)p, b = *(int *)q, i, c, d;

	for (i = c = d = 0; i < n; i++) {
		c += ((a >> i) & 1);
		d += ((b >> i) & 1);
	}

	if (c != d)
		return (d - c);

	for (i = 0; i < n; i++)
		if (((a >> i) & 1) != ((b >> i) & 1))
			return ((a >> i) & 1) ? -1 : 1;

	return 0;
}

int check(int s)
{
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			if (((s >> j) & 1) == 1 && adj[i][j] == 0) break;

		if (((s >> i) & 1) == 1) {
			if (j < n) return 0;
		} else {
			if (j >= n) return 0;
		}
	}

	return 1;
}

int main()
{
	int i, j, c;

	while (scanf("%d", &n) == 1) {
		memset(adj, 0, sizeof(adj));

		for (i = 0; i < n; i++)
			for (j = 0; j < n && (c = getchar()) != EOF;)
				if (c == '-')
					j++;
				else if (c == '*')
					adj[i][j] |= 1, adj[j][i] |= 1, j++;

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				adj[i][j] = !adj[i][j];

		for (i = 0; i < n; i++)
			adj[i][i] = 1;

		for (c = 1, nsets = 0; (c >> n) == 0; c++)
			if (check(c)) sets[nsets++] = c;

		qsort(sets, nsets, sizeof(int), &cmp);

		for (i = 0; i < n; i++) {
			for (j = 0; j < nsets; j++)
				if ((sets[j] >> i) & 1) putchar(j + 'a');
			putchar('\n');
		}

		printf("-----\n");
	}

	return 0;
}
