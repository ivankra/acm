/*
ID: mjf28791
PROG: milk
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>

struct rec {
	int p, a;
} r[8192];

int compare(const void *p, const void *q)
{
	return (((struct rec *)p)->p < ((struct rec *)q)->p) ? -1 : 1;
}

int main()
{
	int i, c, n, m;

	freopen("milk.in", "r", stdin);
	freopen("milk.out", "w", stdout);

	scanf("%d %d", &n, &m);

	for (i = 0; i < m; i++)
		scanf("%d %d", &r[i].p, &r[i].a);

	qsort(r, m, sizeof(struct rec), &compare);

	for (c = 0, i = 0; i < m && n > 0; i++) {
		if (n >= r[i].a) {
			n -= r[i].a;
			c += r[i].p * r[i].a;
		} else {
			c += r[i].p * n;
			break;
		}
	}

	printf("%d\n", c);

	return 0;
}
