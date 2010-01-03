/*
ID: mjf28791
PROG: kimbits
LANG: C
*/
#include <stdio.h>
#include <string.h>

int main()
{
	unsigned c[64][64], s[64][64], n, m, k;

	memset(c, 0, sizeof(c));
	for (n = 0; n < 64; n++)
		for (c[n][0] = 1, k = 1; k <= n; k++)
			c[n][k] = c[n - 1][k - 1] + c[n - 1][k];

	for (n = 0; n < 64; n++)
		for (s[n][0] = c[n][0], k = 1; k < 64; k++)
			s[n][k] = s[n][k - 1] + c[n][k];

	freopen("kimbits.in", "r", stdin);
	freopen("kimbits.out", "w", stdout);

	scanf("%u %u %u", &n, &m, &k);

	for (; n > 0; n--) {
		if (k <= s[n - 1][m]) {
			putchar('0');
		} else {
			putchar('1');
			k -= s[n - 1][m];
			m--;
		}
	}
	putchar('\n');

	return 0;
}
