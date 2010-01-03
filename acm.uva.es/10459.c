#include <stdio.h>
#include <string.h>

#define MAXN 16384
#define MAXE 32768

typedef struct {
	int u, v, h, next;
} edge_t;

edge_t edge[MAXE];
int adj[MAXN], vh[MAXN], nv, ne;

void mkedge(int u, int v)
{
	ne++;
	edge[ne].u = u;
	edge[ne].v = v;
	edge[ne].h = -1;
	edge[ne].next = adj[u];
	adj[u] = ne;
}

/* Returns the height of subtree at which the edge `e' points. */
int subheight(int e)
{
	int h, a;

	if (edge[e].h >= 0)
		return edge[e].h;

	for (edge[e].h = 0, a = adj[edge[e].v]; a != 0; a = edge[a].next) {
		if (edge[a].v == edge[e].u)
			continue;

		h = subheight(a) + 1;
		if (h > edge[e].h)
			edge[e].h = h;
	}

	return edge[e].h;
}

/* Returns height of a tree, rooted at vertex `n' */
int height(int n)
{
	int a, r, h;

	for (r = 0, a = adj[n]; a != 0; a = edge[a].next) {
		h = subheight(a) + 1;
		if (h > r) r = h;
	}

	return r;
}

int main()
{
	int i, k, x, y;

	while (scanf("%d", &nv) == 1) {
		for (i = 1; i <= nv; i++)
			adj[i] = 0;

		for (ne = 0, x = 1; x <= nv && scanf("%d", &k) == 1; x++) {
			while (k-- > 0 && scanf("%d", &y) == 1) {
				mkedge(x, y);
				mkedge(y, x);
			}
		}

		for (i = 1; i <= nv; i++)
			vh[i] = height(i);

		for (x = y = vh[1], i = 2; i <= nv; i++) {
			if (vh[i] < x) x = vh[i];
			if (vh[i] > y) y = vh[i];
		}

		printf("Best Roots  :");
		for (i = 1; i <= nv; i++)
			if (vh[i] == x) printf(" %d", i);
		printf("\nWorst Roots :");
		for (i = 1; i <= nv; i++)
			if (vh[i] == y) printf(" %d", i);
		printf("\n");
	}

	return 0;
}
