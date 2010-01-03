#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char name[128][32];
int adj[128][128], vindex[128], vlow[128], vpar[128], vart[128], n, nindex;

void dfs(int r)
{
	int i, k;

	vlow[r] = vindex[r] = ++nindex;
	vart[r] = 0;

	for (i = 1, k = 0; i <= n; i++) {
		if (adj[i][r] == 0 || i == vpar[r])
			continue;

		if (vindex[i] == 0) {
			vpar[i] = r;
			dfs(i);

			k++;

			if (vlow[i] >= vindex[r])
				vart[r] = 1;

			if (vlow[i] < vlow[r])
				vlow[r] = vlow[i];
		} else {
			if (vindex[i] < vlow[r])
				vlow[r] = vindex[i];
		}
	}

	if (vpar[r] == 0)
		vart[r] = (k > 1);
}


int main()
{
	char s1[256], s2[256];
	int i, j, m, t;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (i = 1; i <= n && scanf(" %[A-Za-z]", name[i]) == 1; i++);

		qsort(&name[1], n, sizeof(name[1]), &strcmp);

		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				adj[i][j] = 0;

		scanf("%d", &m);
		while (m-- > 0 && scanf(" %[A-Za-z] %[A-Za-z]", s1, s2) == 2) {
			for (i = 1; i <= n && strcmp(s1, name[i]) != 0; i++);
			for (j = 1; j <= n && strcmp(s2, name[j]) != 0; j++);
			adj[i][j] = adj[j][i] = 1;
		}

		memset(vindex, 0, sizeof(vindex));
		memset(vpar, 0, sizeof(vpar));
		for (nindex = 0, i = 1; i <= n; i++)
			if (vindex[i] == 0) dfs(i);

		for (j = 0, i = 1; i <= n; i++)
			if (vart[i]) j++;

		printf("%sCity map #%d: %d camera(s) found\n",
			(t == 1) ? "" : "\n", t, j);

		for (i = 1; i <= n; i++)
			if (vart[i]) printf("%s\n", name[i]);
	}

	return 0;
}
