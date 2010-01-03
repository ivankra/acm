#include <stdio.h>

static int a[32][32], cum[32][32], diff[32], n;

static int zeroes()
{
	int i, j, k, m, t, r;

	for (i = 0; i <= n; i++)
		cum[0][i] = cum[i][0] = 0;

	for (i = 1; i <= n; i++) {
		for (j = 1, k = 0; j <= n; j++) {
			k += a[i][j];
			cum[i][j] = cum[i - 1][j] + k;
		}
	}

	for (i = 0, r = 0, diff[0] = 0; i < n; i++) {
		for (j = i + 1; j <= n; j++) {
			for (k = 1; k <= n; k++)
				diff[k] = cum[j][k] - cum[i][k];

			for (k = 0, m = t = 0; k < n; k++) {
				if (diff[k] == diff[k + 1]) {
					t++;
				} else {
					if (t > m) m = t;
					t = 0;
				}
			}

			if (t > m) m = t;

			m *= (j - i);
			if (m > r) r = m;
		}
	}

	return r;
}

int main()
{
	int i, j, c, t;

	for (scanf("%d", &t); t-- > 0;) {
		for (i = 1, n = 32; i <= n; i++) {
			for (j = 1; j <= n;) {
				c = getchar();
				if (c == '0')
					a[i][j++] = 1;
				else if (c == '1')
					a[i][j++] = 0;
				else if (c == '\n' && i == 1 && j > 1)
					n = j - 1;
				else if (c == EOF)
					return 0;
			}
		}

		printf("%d\n", zeroes());
		if (t != 0) printf("\n");
	}

	return 0;
}
