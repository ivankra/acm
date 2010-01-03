#include <stdio.h>

static int solve(int k)
{
	int m, i, n, r, p;

	n = 2 * k;

	for (m = 2;; m++) {
		/* E(p, r, m) = (p + m - 1) % r */

		for (p = 0, r = n; r > k; r--) {
			p = (p + m - 1) % r;
			if (p < k) break;
		}

		if (r == k) break;
	}

	return m;
}

int main()
{
	int k;

	while (scanf("%d", &k) == 1 && k > 0)
		printf("%d\n", solve(k));

	return 0;
}
