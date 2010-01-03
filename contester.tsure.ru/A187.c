#include <stdio.h>

int tab[256][32], stay[256][32], profit[256][32], dist[32], fish[32], decr[32];
int total, nrlakes;

void solve()
{
	static int r[256];
	int i, j, k, t;

	for (k = 1; k <= nrlakes; k++) {
		profit[0][k] = 0;

		for (i = 1; i <= total; i++) {
			j = fish[k] - (i - 1) * decr[k];
			if (j <= 0) break;
			profit[i][k] = profit[i - 1][k] + j;
		}

		for (; i <= total; i++)
			profit[i][k] = profit[i - 1][k];
	}

	for (i = 0; i <= total; i++) {
		tab[i][1] = profit[i][1];
		stay[i][1] = i;
	}

	for (k = 2; k <= nrlakes; k++) {
		for (t = 0; t <= total; t++) {
			tab[t][k] = -1;
			stay[t][k] = 0;
			if (t < dist[k]) continue;

			for (i = 0; i <= total; i++) {
				j = t - dist[k] - i;
				if (j < 0) break;

				j = tab[j][k - 1];
				if (j < 0) continue;

				j += profit[i][k];
				if (j > tab[t][k]) {
					tab[t][k] = j;
					stay[t][k] = i;
				}
			}
		}
	}

	for (k = 1, i = 2; i <= nrlakes; i++)
		if (tab[total][i] > tab[total][k]) k = i;

	for (i = 0; i <= nrlakes; i++)
		r[i] = 0;

	for (i = k, j = total; j > 0 && i >= 1; i--) {
		r[i] = stay[j][i];
		j -= stay[j][i] + dist[i];
	}

	for (i = 1; i < nrlakes; i++)
		printf("%d, ", r[i] * 5);
	printf("%d\n", r[nrlakes] * 5);

	printf("Number of fish expected: %d\n", tab[total][k]);
}

int main()
{
	int i, t;

	for (t = 0; scanf("%d %d", &nrlakes, &total) == 2 && nrlakes != 0;) {
		if (t++ != 0)
			printf("\n");

		total *= 12;

		for (i = 1; i <= nrlakes; i++)
			scanf("%d", &fish[i]);

		for (i = 1; i <= nrlakes; i++)
			scanf("%d", &decr[i]);

		dist[1] = 0;
		for (i = 2; i <= nrlakes; i++)
			scanf("%d", &dist[i]);

		solve();
	}

	return 0;
}
