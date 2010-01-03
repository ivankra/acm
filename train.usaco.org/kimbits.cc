/*
ID: infnty1
PROB: kimbits
LANG: C++
*/
#include <stdio.h>
#include <string.h>

int main()
{
	long long s[64][64], i, j, n, k, m;

	freopen("kimbits.in", "r", stdin);
	freopen("kimbits.out", "w", stdout);

	memset(s, 0, sizeof(s));
	for (i = 0; i < 64; i++) s[0][i] = s[i][0] = 1;
	for (i = 1; i < 64; i++)
		for (j = 1; j < 64; j++)
			s[i][j] = s[i-1][j] + s[i-1][j-1];

	scanf("%lld %lld %lld", &n, &k, &m);

	for (; n > 0; n--) {
		if (m > s[n-1][k]) {
			putchar('1');
			m -= s[n-1][k];
			k--;
		} else {
			putchar('0');
		}
	}
	putchar('\n');

	return 0;
}
