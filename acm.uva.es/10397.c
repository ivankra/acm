// MST
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int x[1024], y[1024], u[1024], m, n, C;
struct edge { int c, a, b; } e[285000];

int cmp(const void *p, const void *q)
{
	return ((struct edge *)p)->c - ((struct edge *)q)->c;
}

int f(int x)
{
	int y, z;
	for (z = x; u[z] != z; z = u[z]);
	while (x != z) { y = u[x]; u[x] = z; x = y; }
	return z;
}

void merge(int x, int y)
{
	x = f(x); y = f(y);
	if (x != y) { u[x] = y; C--; }
}

int main()
{
	int i, j, v1, v2;
	while (scanf("%d", &n) == 1) {
		double r = 0.;

		for (i = 1; i <= n; i++) scanf("%d %d", &x[i], &y[i]);

		C = n;
		for (i = 0; i <= n; i++) u[i] = i;
		scanf("%d", &m);
		while (m-- > 0 && scanf("%d %d", &v1, &v2) == 2) merge(v1,v2);

		for (m = 0, i = 1; i <= n; i++)
			for (j = i+1; j <= n; j++) {
				e[m].a = i; e[m].b = j;
				e[m++].c = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);
			}
		qsort(e, m, sizeof(e[0]), &cmp);

		for (i = 0; i < m && C > 1; i++) {
			if (f(e[i].a) == f(e[i].b)) continue;
			r += sqrt(e[i].c);
			merge(e[i].a, e[i].b);
		}

		printf("%.2f\n", r+1e-10);
	}

	return 0;
}
