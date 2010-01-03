#include <stdio.h>

int main()
{
	int i, t, s, m, k, l, h, n, p, d;
	register int x, v;

	scanf("%d", &t);
	for (i = 0; i < t; i++) {
		scanf("%d %d %d %d", &s, &m, &l, &h);

		for (p = 1, d = -1, k = 0, n = 0; ; k += p) {
			for (x = (k * s), v = 0; x <= h && v < s; v++) {
				if (((x *= s) % (s - 1)) != 0) {
					x = 0;
					break;
				}
				x = (x / (s - 1)) + m;
			}

			if (x > h)
				break;

			if (v == s && x >= l) {
				n++;

				if (d > 0)
					p = k - d;
				d = k;
			}
		}

		printf("%d\n", n);
	}

	return 0;
}
