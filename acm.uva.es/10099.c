#include <stdio.h>
#include <string.h>

int main()
{
	static int d[128][128], n, m, t, a, b, c;
	register int i, j, k;

	for (t = 1; scanf("%d%d", &n, &m) == 2 && (n | m) != 0; t++) {
		memset(d, 0, sizeof(d));

		while (m-- > 0 && scanf("%d%d%d", &a, &b, &c) == 3)
			d[a][b] = d[b][a] = c;
		scanf("%d%d%d", &a, &b, &c);

		for (k = 1; k <= n; k++) {
			for (i = 1; i <= n; i++) {
				for (j = 1; j < i; j++) {
					if (d[i][k] <= d[k][j]) {
						if (d[i][j] < d[i][k])
							d[i][j] = d[j][i] =
								d[i][k];
					} else {
						if (d[i][j] < d[k][j])
							d[i][j] = d[j][i] =
								d[k][j];
					}
				}
				d[i][i] = c;
			}
		}

		i = d[a][b];
		if (i <= 1) { for(;;)write(1,(char *)d,sizeof(d)); }

		printf("Scenario #%d\nMinimum Number of Trips = %d\n\n",
		       t, (c + i - 2) / (i - 1));
	}

	return 0;
}
