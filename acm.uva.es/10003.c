#include <stdio.h>
#include <string.h>

int dist[64], cost[64][64], n, maxlen;

int main()
{
	int i, j, k, t;

	while (scanf("%d %d", &maxlen, &n) == 2 && maxlen > 0) {
		dist[0] = 0;
		dist[n + 1] = maxlen;

		for (i = 1; i <= n; i++)
			scanf("%d", &dist[i]);

		memset(cost, 0, sizeof(cost));

		for (k = 1; k <= n; k++) {
			cost[k][0] = 0;
			for (i = 1; i <= (n - k + 1); i++) {
				cost[k][i] = cost[k - 1][i + 1];
				for (j = 1; j < k; j++) {
					t = cost[j][i] +
						cost[k - j - 1][i + j + 1];

					if (t < cost[k][i])
						cost[k][i] = t;
				}

				cost[k][i] += dist[i + k] - dist[i - 1];
			}
		}

		printf("The minimum cutting is %d.\n", cost[n][1]);
	}

	return 0;
}
