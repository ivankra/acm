#include <stdio.h>
#include <string.h>

int main()
{
	static int d[32][32], n, t, a, b;
	register int i, j, k;

	for (t = 1; ; t++) {
		for (i = 1; i <= 20; i++)
			for (j = 1; j <= 20; j++)
				d[i][j] = 0x3FFFFFFF;

		for (i = 1; i < 20 && scanf("%d", &n) == 1; i++)
			while (n-- > 0 && scanf("%d", &a) == 1)
				d[i][a] = d[a][i] = 1;

		if (i < 20)
			break;

		for (i = 1; i <= 20; i++)
			d[i][i] = 0;

		for (k = 1; k <= 20; k++) {
			for (i = 1; i <= 20; i++) {
				if (i == k || d[i][k] == 0x3FFFFFFF)
					continue;
				for (j = 1; j < i; j++) {
					if (d[i][j] > (d[i][k] + d[k][j]))
						d[i][j] = d[j][i] =
							d[i][k] + d[k][j];
				}
			}
		}

		printf("Test Set #%d\n", t);
		for (scanf("%d", &n); n-- > 0 && scanf("%d%d", &a, &b) == 2;)
			printf("%2d to %2d: %d\n", a, b, d[a][b]);
		printf("\n");
	}

	return 0;
}
