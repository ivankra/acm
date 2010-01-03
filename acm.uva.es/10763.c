#include <stdio.h>
#include <stdlib.h>

#define MAKE(a,b) ((((u_int64_t)(a)) << 32) | ((u_int64_t)(b)))

typedef unsigned long long u_int64_t;
u_int64_t a[1048576];

int compare(const void *p, const void *q)
{
	return (*(u_int64_t *)p > *(u_int64_t *)q) ? 1 : -1;
}

int main()
{
	unsigned x, y;
	int i, n, m;

	while (scanf("%d", &m) == 1 && m > 0) {
		for (n = 0; m-- > 0 && scanf("%u %u", &x, &y) == 2;) {
			a[n++] = MAKE(x, y);
			a[n++] = MAKE(y, x);
		}

		qsort(a, n, sizeof(a[0]), &compare);

		for (i = 0; i < n; i += 2)
			if (a[i] != a[i + 1]) break;

		printf((i < n) ? "NO\n" : "YES\n");
	}

	return 0;
}
