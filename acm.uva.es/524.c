#include <stdio.h>

int main()
{
	static int ring[32], prime[128], free[32], t, u;
	static char buf[65536];
	register int i, j, k, n;
	int m;

	for (prime[0] = 0, i = 1; i < 128; i++)
		prime[i] = 1;
	for (i = 2; i < 128; i++) {
		if (prime[i] == 0)
			continue;
		for (j = i + i; j < 128; j += i)
			prime[j] = 0;
	}

	for (t = 1; scanf("%d", &u) > 0; t++) {	
		if (t > 1) printf("\n");
		printf("Case %d:\n", t);

		for (i = 0; i < 32; i++)
			free[i] = 1;

		for (n = u, m = 0, ring[0] = 1, ring[1] = 1, i = 1; i > 0;) {
			if (i == n) {
				if (prime[ring[i - 1] + 1] == 0) {
					i--;
					continue;
				}

				buf[m++] = '1';
				for (j = 1; j < n; j++) {
					buf[m++] = ' ';
					if ((k = ring[j]) >= 10) {
						buf[m++] = '1';
						buf[m++] = k - 10 + '0';
					} else {
						buf[m++] = k + '0';
					}
				}
				buf[m++] = '\n';

				if (m > (sizeof(buf) - 256)) {
					fwrite(buf, 1, m, stdout);
					m = 0;
				}

				i--;
				continue;
			}

			free[j = ring[i]] = 1;

			for (j++, k = ring[i - 1]; j <= n; j++)
				if (free[j] && prime[j + k]) break;

			if (j <= n) {
				free[j] = 0;
				ring[i] = j;
				ring[++i] = 1;
			} else {
				i--;
			}
		}

		if (m > 0)
			fwrite(buf, 1, m, stdout);
	}

	return 0;
}
