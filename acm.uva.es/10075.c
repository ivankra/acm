#include <stdio.h>
#include <string.h>
#include <math.h>

struct { char s[32]; double p, t; } c[128];

double rad = 3.141592653589793 / 180.;
int d[128][128], z[128][128], n, m, q;

int dist(double p1, double t1, double p2, double t2)
{
	double a = cos(p1) * cos(p2) * cos(t1 - t2) + sin(p1) * sin(p2);
	if (a < -1.) a = -1.;
	if (a > 1.) a = 1.;
	return (int)floor(acos(a) * 6378. + 0.5);
}

int get()
{
	static char s[1024];
	int i;

	scanf(" %s", s);

	for (i = 0; i < n; i++)
		if (strcmp(c[i].s, s) == 0) return i;
	return 0;
}

int main()
{
	int i, j, k, t;

	for (t = 1; scanf("%d %d %d", &n, &m, &q) == 3 && n > 0; t++) {
		for (i = 0; i < n; i++) {
			scanf(" %s %lf %lf", c[i].s, &c[i].p, &c[i].t);
			c[i].p *= rad;
			c[i].t *= rad;
		}

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++)
				z[i][j] = 0;
			z[i][i] = 1;
			d[i][i] = 0;
		}

		while (m-- > 0) {
			i = get();
			j = get();
			z[i][j] = 1;
			d[i][j] = dist(c[i].p, c[i].t, c[j].p, c[j].t);
		}

		for (k = 0; k < n; k++) {
			for (i = 0; i < n; i++) {
				if (z[i][k] == 0) continue;

				for (j = 0; j < n; j++)
					if (z[k][j] != 0 && (z[i][j] == 0 ||
					      (d[i][k] + d[k][j]) < d[i][j])) {
						d[i][j] = d[i][k] + d[k][j];
						z[i][j] = 1;
					}
			}
		}

		printf("%sCase #%d\n", (t == 1) ? "" : "\n", t);

		while (q-- > 0) {
			i = get();
			j = get();

			if (z[i][j])
				printf("%d km\n", d[i][j]);
			else
				printf("no route exists\n");
		}
	}

	return 0;
}
