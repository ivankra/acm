#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct { int x, y, c; } edge_t;

edge_t edg[256];
int csum[256], best, n, m;

int ufind(int u[], int x)
{
	int r = x;
	while (u[r] != r) r = u[r];
	return (u[x] = r);
}

void search(int s, int u0[], int rem1, int v0[], int rem2, int cost)
{
	int u[16], v[16], i;

	for (i = 0; i < n; i++)
		v[i] = v0[i];

	if (rem1 == 0) {
		for (; rem2 > 0 && s < m; s++) {
			if (ufind(v, edg[s].x) != ufind(v, edg[s].y)) {
				cost += edg[s].c;
				v[v[edg[s].x]] = v[edg[s].y];
				rem2--;
			}
		}

		if (rem2 == 0 && cost < best) best = cost;
		return;
	}

	for (;; s++) {
		if ((s + rem1 + rem2) > m)
			break;

		i = cost + csum[s + rem1 + rem2] - csum[s];
		if (i >= best)
			break;

		if (ufind(u0, edg[s].x) != ufind(u0, edg[s].y)) {
			for (i = 0; i < n; i++) u[i] = u0[i];
			u[u[edg[s].x]] = u[edg[s].y];
			search(s + 1, u, rem1 - 1, v, rem2, cost + edg[s].c);
		}

		if (rem2 > 0 && ufind(v, edg[s].x) != ufind(v, edg[s].y)) {
			v[v[edg[s].x]] = v[edg[s].y];
			cost += edg[s].c;
			rem2--;
		}
	}
}

int has_bridge()
{
	int u[16], i, j, k;

	for (k = -1; k < m; k++) {
		for (i = 0; i < n; i++)
			u[i] = i;

		for (i = 0; i < m; i++) {
			if (k == i || ufind(u, edg[i].x) == ufind(u, edg[i].y))
				continue;
			u[u[edg[i].x]] = u[edg[i].y];
		}

		for (j = ufind(u, 0), i = 0; i < n; i++)
			if (ufind(u, i) != j) return 1;
	}

	return 0;
}

void rmdup()
{
	int a[16][16], i, j;

	memset(a, 0, sizeof(a));
	for (i = j = 0; i < m; i++) {
		a[edg[i].x][edg[i].y]++;
		a[edg[i].y][edg[i].x]++;
		if (edg[i].x == edg[i].y || a[edg[i].x][edg[i].y] > 2) continue;

		if (i != j) edg[j] = edg[i];
		j++;
	}
	m = j;
}

int cmp(const void *p, const void *q)
{
	return ((edge_t *)p)->c - ((edge_t *)q)->c;
}

int main()
{
	int u[16], i;

	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		for (i = 0; i < m; i++) {
			scanf("%d %d %d", &edg[i].x, &edg[i].y, &edg[i].c);
			edg[i].x--;
			edg[i].y--;
		}

		qsort(edg, m, sizeof(edg[0]), &cmp);
		rmdup();

		if (m < 2 * (n - 1) || has_bridge()) {
			printf("No way!\n");
			continue;
		}

		for (csum[0] = 0, i = 0; i < m; i++)
			csum[i + 1] = csum[i] + edg[i].c;

		for (i = 0; i < n; i++)
			u[i] = i;

		best = 0x7FFFFFFF;

		search(0, u, n - 1, u, n - 1, 0);

		if (best > csum[m])
			printf("No way!\n");
		else
			printf("%d\n", best);
	}

	return 0;
}
