#include <stdio.h>
#include <string.h>

int main()
{
	static int a[128], b[128], n, m, t, x;
	register int i;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		memset(a, 0, sizeof(a));
		a[0] = 1;

		while (n-- > 0 && scanf("%d", &x) == 1) {
			x = (x < 0) ? ((m - (x % m)) % m) : (x % m);

			for (i = 0; i < m; i++)
				b[i] = 0;

			for (i = 0; i < m; i++) {
				if (a[i]) {
					b[(i + x) % m] = 1;
					b[(i + m - x) % m] = 1;
				}
			}

			for (i = 0; i < m; i++)
				a[i] = b[i];
		}

		printf(a[0] ? "Divisible\n" : "Not divisible\n");
	}			

	return 0;
}
