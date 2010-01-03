#include <stdio.h>
#include <string.h>

typedef unsigned long long num;

int main()
{
	static num f[32][32], g[16];
	static int cvt[256], n;
	static char s[32];
	int i, j, k, p;

	for (i = 0; i < 16; i++)
		cvt["0123456789ABCDEF"[i]] = i;

	for (i = 0; i < 6; i++)
		cvt["abcdef"[i]] = 10+i;

	while (scanf(" %s", s) == 1) {
		n = strlen(s);

		if (n == 1) {
			printf("1\n");
			continue;
		}

		for (i = 1; i <= n; i++)
			f[0][i] = 1;
		f[0][0] = f[0][n + 1] = 0;
		g[0] = n;

		for (k = 1, p = 0; k < n; k++, p++) {
			g[k] = f[k][0] = f[k][n + 1] = 0;
			if (s[p] == '?') {
				for (i = 1; i <= n; i++) {
					f[k][i] = g[p] - f[p][i-1] - f[p][i] - f[p][i+1];
					g[k] += f[k][i];
				}
			} else {
				j = cvt[s[p]];
				for (i = 1; i <= n; i++)
					f[k][i] = f[p][j];
				f[k][j - 1] = f[k][j] = f[k][j + 1] = 0;
				for (i = 1; i <= n; i++)
					g[k] += f[k][i];
			}
		}

		if (s[n - 1] == '?')
			printf("%llu\n", g[n - 1]);
		else
			printf("%llu\n", f[n - 1][cvt[s[n - 1]]]);
	}

	return 0;
}
