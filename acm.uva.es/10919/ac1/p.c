#include <stdio.h>
#include <stdlib.h>

int x[128], k;

int cmp(const void *p, const void *q)
{
	return *(int *)p - *(int *)q;
}

int f(int z)
{
	int a, b, c;

	for (a = 0, b = k - 1; a <= b;)
		if (x[c = (a + b) >> 1] < z)
			a = c + 1;
		else if (x[c] > z)
			b = c - 1;
		else
			return 1;

	return 0;
}

int main()
{
	int i, m, c, r, w;

	while (scanf("%d %d", &k, &m) == 2 && k > 0) {
		for (i = 0; i < k; i++)
			scanf("%d", &x[i]);
		qsort(x, k, sizeof(x[0]), &cmp);

		for (i = 1; m-- > 0 && scanf("%d %d", &c, &r) == 2;) {
			while (c-- > 0 && scanf("%d", &w) == 1) r -= f(w);
			if (r > 0) i = 0;
		}

		printf(i ? "yes\n" : "no\n");
	}

	return 0;
}
