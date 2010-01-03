#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int u, v, c; } edge_t;

edge_t edge[16384];
int n, m;

int compare(const void *p, const void *q)
{
	return ((edge_t *)q)->c - ((edge_t *)p)->c;
}

int solve()
{
	static int cov[256], result;
	int i;

	if (m <= 0)
		return 0;

	if (n <= 1)
		return 0;

	qsort(edge, m, sizeof(edge[0]), &compare);
	memset(cov, 0, sizeof(cov));

	for (cov[0] = 1, result = edge[0].c;;) {
		for (i = 0; i < m; i++) {
			if (cov[edge[i].u] && !cov[edge[i].v]) break;
			if (!cov[edge[i].u] && cov[edge[i].v]) break;
		}

		if (i >= m) break;

		cov[edge[i].u] = cov[edge[i].v] = 1;
		if (result > edge[i].c) result = edge[i].c;
	}

	return result;
}

int main()
{
	int i, c, t;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d %d", &n, &m) == 2; c++) {
		for (i = 0; i < m; i++)
			scanf("%d %d %d", &edge[i].u, &edge[i].v, &edge[i].c);

		printf("Case #%d: %d\n", c, solve());
	}

	return 0;
}
