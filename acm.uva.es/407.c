#include <stdio.h>
#include <math.h>

#define EPS 1e-12

int adj_in[32][32], adj_out[32][32], gx[32], gy[32], g_ir[32], g_or[32], n;
double rpm[32];

int sq(int x)
{
	return (x * x);
}

char *solve()
{
	static int a[32], s[32];
	int i, j, k;
	long double v;

	for (i = 0; i <= n; i++) {
		adj_in[i][i] = adj_out[i][i] = 0;
		for (j = i + 1; j <= n; j++) {
			k = sq(gx[i] - gx[j]) + sq(gy[i] - gy[j]);
			if (k < sq(g_ir[i] + g_ir[j]) || k < sq(g_or[i] + g_or[j]))
				return "Error -- Overlapping Gears\n";

			adj_in[i][j] = adj_in[j][i] = (k == sq(g_ir[i] + g_ir[j]));
			adj_out[i][j] = adj_out[j][i] = (k == sq(g_or[i] + g_or[j]));
		}
	}

	for (a[0] = 1, i = 1; i <= n; i++)
		a[i] = 0;

	for (s[0] = 0, k = 1; k > 0;) {
		i = s[--k];

		for (j = 0; j <= n; j++) {
			if (adj_in[i][j] == 0)
				continue;

			v = -rpm[i] * g_ir[i] / (double)g_ir[j];
			if (a[j] == 0) {
				rpm[j] = v;
				a[j] = 1;
				s[k++] = j;
			} else if (fabs(rpm[j] - v) > EPS) {
				return "Error -- Conflicting Gear Rotation\n";
			}
		}

		for (j = 0; j <= n; j++) {
			if (adj_out[i][j] == 0)
				continue;

			v = -rpm[i] * g_or[i] / (double)g_or[j];
			if (a[j] == 0) {
				rpm[j] = v;
				a[j] = 1;
				s[k++] = j;
			} else if (fabs(rpm[j] - v) > EPS) {
				return "Error -- Conflicting Gear Rotation\n";
			}
		}
	}

	for (i = 1; i <= n; i++)
		printf(a[i] ? "%2d: %c %.2f\n" : "%2d: Warning -- Idle Gear\n",
		       i, (rpm[i] < 0) ? 'L' : 'R', fabs(rpm[i]));

	return "";
}

int main()
{
	int i, t;

	for (t = 1;; t++) {
		i = scanf("%d %d %d %d %lf %d",
			  &gx[0], &gy[0], &g_ir[0], &g_or[0], &rpm[0], &n);
		if (i != 6) break;

		for (i = 1; i <= n; i++)
			scanf("%d %d %d %d", &gx[i], &gy[i], &g_ir[i], &g_or[i]);

		printf("Simulation #%d\n", t);
		printf("%s\n", solve());
	}

	return 0;
}
