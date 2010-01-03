#include <stdio.h>
#include <ctype.h>

long long gcd(long long x, long long y)
{
	return (y == 0) ? x : gcd(y, x % y);
}

int main()
{
	static long long p[32], x, y, z;
	static char s[1024];
	int n, m, i, t;

	for (p[0] = 1, i = 1; i < 32; i++)
		p[i] = 10 * p[i - 1];

	for (t = 1; scanf("%d %s", &m, s) == 2 && m >= 0; t++) {
		for (i = 0; s[i] != '\0' && s[i] != '.'; i++);
		if (s[i] == '.') i++;

		for (x = 0, n = 0; s[i] != '\0'; i++) {
			if (isdigit(s[i])) {
				n++;
				x = x * 10LL + (long long)(s[i] - '0');
			}
		}

		if (m > 0) {
			x = x - (x / p[m]);
			y = p[n] - p[n - m];
		} else {
			y = p[n];
		}

		z = gcd(x, y);
		if (z != 0)
			x /= z, y /= z;

		printf("Case %d: %lld/%lld\n", t, x, y);
	}

	return 0;
}
