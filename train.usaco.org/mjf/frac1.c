/*
ID: mjf28791
PROG: frac1
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
 	int p, q;
} frac_t;

int gcd(int x, int y)
{
	return (x == 0) ? y : gcd(y % x, x);
}

int compare(const void *x, const void *y)
{
	frac_t *a = (frac_t *)x, *b = (frac_t *)y;
	return (a->p * b->q - b->p * a->q);
}

int main()
{
	static frac_t f[65536];
	int i, j, n, k;

	freopen("frac1.in", "r", stdin);
	freopen("frac1.out", "w", stdout);

	scanf("%d", &n);

	for (k = 0, j = 1; j <= n; j++)
		for (i = 0; i <= j; i++)
			if (gcd(i, j) == 1)
				f[k].p = i, f[k].q = j, k++;

	qsort(f, k, sizeof(f[0]), &compare);

	for (i = 0; i < k; i++)
		printf("%d/%d\n", f[i].p, f[i].q);

	return 0;
}
