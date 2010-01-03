/*
ID: mjf28791
PROG: ariprog
LANG: C
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int a[65536], b[524288], n;

typedef struct { int a, b; } pair_t;

int cmp(const void *p, const void *q)
{
	pair_t *x = (pair_t *)p, *y = (pair_t *)q;
	return (x->b == y->b) ? (x->a - y->a) : (x->b - y->b);
}

int check(int s, int d, int l)
{
	while (l-- > 1)
		if (b[s += d] == 0) return 0;
	return 1;
}

int main()
{
	static pair_t r[16384];
	int i, j, k, m, len, len1;

	freopen("ariprog.in", "r", stdin);
	freopen("ariprog.out", "w", stdout);
	scanf("%d %d", &len, &m);

	memset(b, 0, sizeof(b));
	for (n = 0, i = 0; i <= m; i++)
		for (j = i; j <= m; j++)
			b[i * i + j * j] = 1;

	for (n = 0, i = 0, j = 2 * m * m; i <= j; i++)
		if (b[i]) a[n++] = i;
	a[n] = a[n - 1];

	if (len == 3) {
		for (i = 1, m = 0; i <= a[n]; i++)
			for (j = 0; j < n; j++)
				if (b[a[j] + i] && b[a[j] + i + i]) {
					printf("%d %d\n", a[j], i);
					m++;
				}
		if (m == 0) printf("NONE\n");
		return 0;
	}

	len1 = len - 1;

	for (m = 0, i = 0; i < n; i++) {
		for (j = i + 2; j < n; j++) {
			if ((a[j] - a[i]) & 7) continue;

			if (b[(a[i] + a[j]) >> 1] == 0) continue;

			k = a[i] + len1 * ((a[j] - a[i]) >> 1);
			if (k > a[n]) break;
			if (b[k] == 0) continue;

			if (check(a[j], (a[j] - a[i]) >> 1, len - 3)) {
				r[m].a = a[i];
				r[m].b = (a[j] - a[i]) >> 1;
				m++;
			}
		}
	}

	qsort(r, m, sizeof(r[0]), &cmp);

	for (i = 0; i < m; i++)
		printf("%d %d\n", r[i].a, r[i].b);

	if (m == 0) printf("NONE\n");

	return 0;
}
