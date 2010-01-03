#include <stdio.h>
#include <string.h>

int main()
{
	static int d[64][32][32], s[64][32][32];
	int i, j, k, m, n, t, x, y;

	for (t = 0; scanf("%d", &m) == 1; t++) {
		printf("matrix for city %d\n", t);

		memset(d, 0, sizeof(d));
		memset(s, 0, sizeof(s));

		for (n = -1; m-- > 0 && scanf("%d %d", &x, &y) == 2;) {
			d[1][x][y]++;
			s[1][x][y]++;
			if (x > n) n = x;
			if (y > n) n = y;
		}
		n++;

		for (m = 2; m < 64; m++) {
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					for (d[m][i][j] = 0, k = 0; k < n; k++)
						d[m][i][j] += d[m - 1][i][k] * d[1][k][j];

					s[m][i][j] = s[m - 1][i][j];

					if (m > n && d[m][i][j] != 0)
						s[m][i][j] = -1;
					else
						s[m][i][j] += d[m][i][j];
				}
			}
		}

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++)
				printf(j ? " %d" : "%d", s[63][i][j]);
			printf("\n");
		}
	}

	return 0;
}
