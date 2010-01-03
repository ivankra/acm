#include <stdio.h>

int f[64][1024], p[64][32], c[64], s[64], n, t;

int main()
{
	int i, j, k, m;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (s[0] = 0, i = 1; i <= n && scanf("%d", &c[i]) == 1; i++) {
			s[i] = s[i - 1] + c[i];
			p[i][0] = 0;
			for (j = 1; j <= c[i] && scanf("%d", &p[i][j]) == 1; j++)
				p[i][j] = p[i][j - 1] + 10 - p[i][j];
		}

		for (i = 0; i <= s[1]; i++)
			f[1][i] = p[1][i];

		for (m = 2; m <= n; m++) {
			for (k = 0; k <= s[m]; k++) {
				i = k - s[m - 1];
				if (i < 0) i = 0;

				f[m][k] = -0x3FFFFFFF;
				for (; i <= k && i <= c[m]; i++) {
					j = f[m - 1][k - i] + p[m][i];
					if (j > f[m][k]) f[m][k] = j;
				}
			}
		}

		for (i = 0, m = 0; i <= s[n]; i++)
			if (f[n][i] > m) m = f[n][i];

		printf("%sWorkyards %d\nMaximum profit is %d.\nNumber of pruls to buy:",
		       (t > 1) ? "\n" : "", t, m);
		for (i = j = 0; i <= s[n] && j < 10; i++)
			if (f[n][i] == m) j++, printf(" %d", i);
		printf("\n");
	}

	return 0;
}
