#include <stdio.h>
#include <string.h>

double p[16], f[128][16];

double solve(char *fmt, int r)
{
	int i, j, k, n;

	n = strlen(fmt);

	for (i = 1; i <= n; i++) {
		for (j = 0; j < 11; j++) {
			if (fmt[i-1] != '*') {
				k = fmt[i-1] - '0';
				f[i][j] = f[i-1][((j - k + 11) * 10) % 11];
				continue;
			}

			for (f[i][j] = 0., k = 0; k <= 9; k++)
				f[i][j] += p[k] * f[i-1][((j - k + 11) * 10) % 11];
		}
	}

	return f[n][r % 11];
}

int main()
{
	char s[1024];
	int i, x, t, q;

	memset(f, 0, sizeof(f));
	f[0][0] = 1.;

	for (t = 1; scanf("%d", &x) == 1 && x == 10; t++) {
		printf("Case %d:\n", t);

		for (i = 0; i < 10 && scanf("%d %lf", &x, &p[10]) == 2; i++)
			p[x] = p[10];

		for (scanf("%d", &q); q-- > 0 && scanf(" %[0-9*] %d", s, &x) == 2;)
			printf("%.8f\n", solve(s, x));
	}

	return 0;
}
