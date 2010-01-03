#include <stdio.h>
#include <stdlib.h>

#define MAXV 65536
#define MAXE 262144

int adj[MAXE], adjnext, n, t;
int r[MAXE][2], nr;
struct { int a, d, w, p; } v[MAXV];

void dfs(int x)
{
	int i, y;

	v[x].w = v[x].d = ++t;

	for (i = v[x].a; adj[i] >= 0; i++) {
		y = adj[i];

		if (v[x].p == y)
			continue;

		if (v[y].d != 0) {
			if (v[y].d < v[x].w)
				v[x].w = v[y].d;
		} else {
			v[y].p = x;
			dfs(y);

			if (v[y].w == v[y].d) {
				r[nr][0] = x;
				r[nr][1] = y;
				nr++;
			}

			if (v[y].w < v[x].w)
				v[x].w = v[y].w;
		}
	}
}

int compare(const void *p, const void *q)
{
	if (((int *)p)[0] != ((int *)q)[0])
		return (((int *)p)[0] - ((int *)q)[0]);
	return (((int *)p)[1] - ((int *)q)[1]);
}

int main()
{
	int i, a, m;

	while (scanf("%d", &n) == 1) {
		for (i = 0, adj[0] = -1; i < n; i++)
			v[i].a = v[i].d = 0;

		for (adjnext = 1, i = 0; i < n; i++) {
			scanf("%d ( %d )", &a, &m);
			v[a].a = adjnext;
			while (m-- > 0 && scanf("%d", &a) == 1)
				adj[adjnext++] = a;
			adj[adjnext++] = -1;
		}

		for (t = 0, nr = 0, i = 0; i < n; i++) {
			if (v[i].d == 0) {
				v[i].p = -1;
				dfs(i);
			}
		}

		for (i = 0; i < nr; i++) {
			if (r[i][0] > r[i][1]) {
				a = r[i][0];
				r[i][0] = r[i][1];
				r[i][1] = a;
			}
		}
		qsort((void *)r, nr, sizeof(r[0]), &compare);

		printf("%d critical links\n", nr);
		for (i = 0; i < nr; i++)
			printf("%d - %d\n", r[i][0], r[i][1]);
		printf("\n");
	}

	return 0;
}
