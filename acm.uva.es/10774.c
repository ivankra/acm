#include <stdio.h>

static int surv(int x)
{
	register int r;
	for (r = 0; (x >> r) > 1; r++);
	return ((x - (1 << r)) << 1) + 1;
}

int main()
{
	int t, n, k, s, x;

	for (scanf("%d", &n), t = 1; t <= n && scanf("%d", &x) == 1; t++) {
		s = surv(x);
		for (k = 0; s != x;) {
			x = s;
			s = surv(x);
			k++;
		}

		printf("Case %d: %d %d\n", t, k, s);
	}

	return 0;
}
