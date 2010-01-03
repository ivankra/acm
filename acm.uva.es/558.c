#include <stdio.h>

#include <limits.h>
#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

struct { int x, y, w; } e[2048];
int v[1024], nv, ne;

int solve(void)
{
	register int i, j, n, f;

	for (v[0] = 0, i = 1; i < nv; i++)
		v[i] = INT_MAX;

	for (n = 0;; n++) {
		for (f = 0, i = 0; i < ne; i++) {
			j = v[e[i].x] + e[i].w;
			if (j < v[e[i].y]) {
				v[e[i].y] = j;
				f = 1;
			}
		}

		if (f == 0)
			return 0;

		if (n > nv)
			return 1;
	}
}

int main(void)
{
	int i, j, n;

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d %d", &nv, &ne);
		for (j = 0; j < ne; j++)
			scanf("%d %d %d", &e[j].x, &e[j].y, &e[j].w);

		printf(solve() ? "possible\n" : "not possible\n");
	}

	return 0;
}
