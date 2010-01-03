#include <stdio.h>

int main()
{
	int t, m, n, a, x, y;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &m, &n) == 2;) {
		for (x = 0, y = 0; n-- > 0 && scanf("%d", &a) == 1;) {
			if ((a + a) <= m) {
				x = (a > x) ? a : x;
				y = ((m - a) > y) ? (m - a) : y;
			} else {
				x = ((m - a) > x) ? (m - a) : x;
				y = (a > y) ? a : y;
			}
		}

		printf("%d %d\n", x, y);
	}

	return 0;
}
