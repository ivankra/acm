#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int id;
	int indeg;
	int reachable;
} vertex_t;

typedef struct {
	int a, b;
} edge_t;

static vertex_t *vert;
static edge_t *edges;
static int nr_vert, max_vert, nr_edges, max_edges;

static int map(int k)
{
	register int i;

	for (i = 0; i < nr_vert; i++)
		if (vert[i].id == k) return i;

	if (nr_vert >= max_vert)
		vert = (vertex_t *)realloc(vert, (max_vert *= 2) * sizeof(vertex_t));

	i = nr_vert++;
	vert[i].id = k;
	vert[i].indeg = 0;
	vert[i].reachable = 0;
	return i;
}

static void edge(int a, int b)
{
	if (nr_edges >= max_edges)
		edges = (edge_t *)realloc(edges, (max_edges *= 2) * sizeof(edge_t));

	edges[nr_edges].a = a;
	edges[nr_edges].b = b;
	vert[b].indeg++;
	nr_edges++;
}

static int istree()
{
	static int root;
	register int i, j;

	if (nr_vert == 0) return 1;

	for (i = 0, root = -1; i < nr_vert; i++) {
		if (vert[i].indeg == 0) {
			if (root < 0)
				root = i;
			else
				return 0;
		} else if (vert[i].indeg != 1) {
			return 0;
		}
	}

	if (root < 0)
		return 0;

	vert[root].reachable = 1;

	do {
		for (i = 0, j = 0; i < nr_edges; i++) {
			if (vert[edges[i].a].reachable &&
			    !vert[edges[i].b].reachable) {
				vert[edges[i].b].reachable = 1;
				j++;
			}
		}
	} while (j > 0);

	for (i = 0; i < nr_vert; i++)
		if (!vert[i].reachable) return 0;

	return 1;
}

int main()
{
	static int t, i, a, b;

	vert = (vertex_t *)malloc((max_vert = 1024) * sizeof(vertex_t));
	edges = (edge_t *)malloc((max_edges = 1024) * sizeof(edge_t));

	for (t = 1;; t++) {
		nr_vert = 0;
		nr_edges = 0;

		for (i = 0; scanf("%d %d", &a, &b) == 2; i++) {
			if (a < 0 || b < 0) {
				i = -1;
				break;
			}
			if (a == 0 || b == 0)
				break;
			edge(map(a), map(b));
		}

		if (i < 0)
			break;

		printf("Case %d %s a tree.\n", t, istree() ? "is" : "is not");
	}

	return 0;
}
