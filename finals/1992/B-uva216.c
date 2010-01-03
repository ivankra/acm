#include <stdio.h>
#include <string.h>
#include <math.h>

double hypot(double, double);

double adj[16][16], best, len;
int x[16], y[16], p[16], u[16], best_p[16], n;

void search(int k)
{
	int i, x, y;

	if (k >= n) {
		if (len < best) {
			best = len;
			for (i = 0; i < n; i++) best_p[i] = p[i];
		}
		return;
	}

	if (len > best)
		return;

	for (x = p[k - 1], y = 0; y < n; y++) {
		if (u[y]) continue;
		u[p[k] = y] = 1;
		len += adj[x][y];
		search(k + 1);
		len -= adj[x][y];
		u[y] = 0;
	}
}

int main()
{
	int i, j, t;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		printf("**********************************************************\n"
		       "Network #%d\n", t);

		for (i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				adj[i][j] = hypot(x[i] - x[j], y[i] - y[j]);

		best = 1. / 0.;
		len = 0.;
		memset(u, 0, sizeof(u));

		for (i = 0; i < n; i++) {
			u[p[0] = i] = 1;
			search(1);
			u[i] = 0;
		}

		for (i = 0; i < n; i++)
			p[i] = best_p[i];

		for (i = 1; i < n; i++) {
			printf(
				"Cable requirement to connect (%d,%d) to (%d,%d) is %.2f feet.\n",
				x[p[i - 1]], y[p[i - 1]],
				x[p[i]], y[p[i]],
				adj[p[i - 1]][p[i]] + 16.
			);
		}

		printf("Number of feet of cable required is %.2f.\n", best + 16. * (n - 1));
	}

	return 0;
}
