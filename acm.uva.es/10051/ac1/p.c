#include <stdio.h>
#include <string.h>

char *facename[] = { "front", "back", "left", "right", "top", "bottom" };
int opposite[] = { 1, 0, 3, 2, 5, 4 };

int ncubes, cube[1024][8];
int cid[8192], cface[8192], cpred[8192], cheight[8192], best[128];

void solve()
{
	static int p[8192];
	int i, j, k;

	memset(best, 0, sizeof(best));

	cheight[0] = 0;
	for (k = 1, i = 0; i < ncubes; i++) {
		for (j = 0; j < 6; j++) {
			cid[k + j] = i;
			cface[k + j] = j;
			cpred[k + j] = best[cube[i][j]];
			cheight[k + j] = 1 + cheight[cpred[k + j]];
		}

		for (j = 0; j < 6; j++, k++)
			if (cheight[k] > cheight[best[cube[i][opposite[j]]]])
				best[cube[i][opposite[j]]] = k;
	}

	for (j = i = 1; i < k; i++)
		if (cheight[i] > cheight[j]) j = i;

	printf("%d\n", cheight[j]);

	for (i = 0; j > 0; j = cpred[j])
		p[i++] = j;

	while (i-- > 0)
		printf("%d %s\n", cid[p[i]] + 1, facename[cface[p[i]]]);
}

int main()
{
	int i, j, t;

	for (t = 1; scanf("%d", &ncubes) == 1 && ncubes > 0; t++) {
		for (i = 0; i < ncubes; i++)
			for (j = 0; j < 6; j++)
				scanf("%d", &cube[i][j]);

		printf("%sCase #%d\n", t == 1 ? "" : "\n", t);
		solve();
	}

	return 0;
}
