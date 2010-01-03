#include <stdio.h>
#include <string.h>

char name[65536][16];
int nr;

int get()
{
	int i;

	scanf(" %s", name[nr]);

	for (i = 0; i < nr; i++)
		if (strcmp(name[i], name[nr]) == 0) return i;

	return nr++;
}

int main()
{
	static int adj[256][256], t, m, c, x, y;
	int i, j, k;

	for (t = 1; scanf("%d", &c) == 1 && c > 0; t++) {
		memset(adj, 0, sizeof(adj));

		for (nr = 0; c-- && scanf("%d", &m) == 1;)
			if (m > 0) 
				for (x = get(); m-- > 1; x = y)
					adj[x][y = get()] = 1;

		for (scanf("%d", &c); c-- > 0;) {
			x = get(); y = get();
			adj[x][y] = 1;
		}

		for (k = 0; k < nr; k++)
			for (i = 0; i < nr; i++)
				if (adj[i][k])
					for (j = 0; j < nr; j++)
						adj[i][j] |= adj[k][j];

		for (k = 0, i = 0; i < nr; i++)
			for (j = i + 1; j < nr; j++)
				if (adj[i][j] == 0 && adj[j][i] == 0) k++;

		if (k == 0) {
			printf("Case %d, no concurrent events.\n", t);
		} else {
			printf("Case %d, %d concurrent events:\n", t, k);
			if (k > 2) k = 2;

			for (i = 0; i < nr && k > 0; i++)
				for (j = i + 1; j < nr && k > 0; j++)
					if (adj[i][j] == 0 && adj[j][i] == 0)
						printf(--k ? "(%s,%s) " : "(%s,%s) \n",
							name[i], name[j]);
		}
	}

	return 0;
}
