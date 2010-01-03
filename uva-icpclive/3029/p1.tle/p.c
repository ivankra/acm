#include <stdio.h>

int main()
{
	static int cum[1024][1024], diff[1024], h, w, t, res;
	int i, j, k, r1, r2;

	scanf("%d", &t);

	while (t-- > 0 && scanf("%d %d", &h, &w) == 2) {
		for (i = 0; i <= w; i++)
			cum[0][i] = 0;

		for (i = 1; i <= h; i++)
			for (j = 1; j <= w; j++)
				cum[i][j] = 1;

		for (i = 1; i <= h; i++) {
			for (j = 1; j <= w;) {
				k = getchar();
				if (k == 'R')
					j++;
				else if (k == 'F')
					cum[i][j++] = 0;
			}
		}

		for (i = 1; i <= h; i++) {
			for (cum[i][0] = k = 0, j = 1; j <= w; j++) {
				k += cum[i][j];
				cum[i][j] = cum[i - 1][j] + k;
			}
		}

		for (res = 0, r1 = 0; r1 < h; r1++) {
			for (r2 = r1 + 1; r2 <= h; r2++) {
				for (i = 0; i <= w; i++)
					diff[i] = cum[r2][i] - cum[r1][i];

				for (i = 0, j = k = 0; i < w; i++) {
					if (diff[i] == diff[i + 1]) {
						j++;
					} else {
						if (j > k) k = j;
						j = 0;
					}
				}

				if (j > k) k = j;

				k *= (r2 - r1) * 3;
				if (k > res) res = k;
			}
		}

		printf("%d\n", res);
	}

	return 0;
}
