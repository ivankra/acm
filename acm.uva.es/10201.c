#include <stdio.h>

#define INF 0x3FFFFFFF

int main()
{
	static int dist[128], cost[128], tab[128][256], t, n;
	static char buf[1024];
	int i, k, d, s1, s2, f1, f2;

	for (scanf("%d", &t); t-- > 0;) {
		while (gets(buf) != NULL && sscanf(buf, "%d", &dist[0]) != 1);

		for (n = 1; gets(buf); n++)
			if (sscanf(buf, "%d %d", &dist[n], &cost[n]) != 2)
				break;

		dist[n] = dist[0];
		cost[n] = 0;
		n++;

		dist[0] = 0;
		cost[0] = 0;

		for (i = 0; i < n; i++)
			for (k = 0; k <= 200; k++)
				tab[i][k] = INF;

		for (i = 1; i < n && dist[i] <= 100; i++)
			for (k = 100 - dist[i]; k >= 0; k--)
				tab[i][k] = 0;

		for (s2 = 1; s2 < n; s2++) {
			for (s1 = s2 - 1; s1 >= 1; s1--) {
				d = dist[s2] - dist[s1];
				if (d > 200)
					continue;

				for (f1 = d; f1 <= 200; f1++) {
					if (tab[s1][f1] == INF)
						continue;

					f2 = f1 - d;
					if (tab[s2][f2] > tab[s1][f1])
						tab[s2][f2] = tab[s1][f1];
				}
			}

			for (k = tab[s2][200], i = 199; i >= 0; i--)
				if (tab[s2][i] < k)
					k = tab[s2][i];
				else if (tab[s2][i] > k)
					tab[s2][i] = k;

			if (s2 != (n - 1)) {
				for (i = 1; i <= 200; i++) {
					k = tab[s2][i - 1] + cost[s2];
					if (tab[s2][i] > k) tab[s2][i] = k;
				}
			}

		}

		for (i = 100, k = INF; i <= 200; i++)
			if (tab[n - 1][i] < k) k = tab[n - 1][i];

		if (k == INF)
			printf("Impossible\n");
		else
			printf("%d\n", k);

	       if (t > 0) printf("\n");
	}

	return 0;
}
