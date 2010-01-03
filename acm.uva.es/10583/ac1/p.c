#include <stdio.h>

int main()
{
	static int x, y, n, m, r, t, p[65536];
	register int i;

	for (t = 1; scanf("%d %d", &n, &m) == 2 && n > 0; t++) {
		for (r = n, i = 1; i <= n; i++)
			p[i] = i;

		while (m-- > 0 && scanf("%d %d", &x, &y) == 2) {
			for (i = x; p[i] != i; i = p[i]);
			p[x] = i;

			for (i = y; p[i] != i; i = p[i]);
			p[y] = i;

			if (p[x] == p[y])
				continue;

			p[p[x]] = i;
			r--;
		}

		printf("Case %d: %d\n", t, r);
	}

	return 0;
}
