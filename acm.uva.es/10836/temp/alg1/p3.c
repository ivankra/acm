#include <stdio.h>
#include <math.h>

static double logf[512], logc[4];
static int n, c[4], r[4];

static void look()
{
	static int g[4], a[4], rmin[4], rmax[4];
	static double rlog;
	register int i, j;
	double u;

	for (i = 0, j = 0; i < 4; i++)
		j += c[i];

	for (i = 0; i < 4; i++) {
		g[i] = (c[i] * n + (j >> 1)) / j;

		rmin[i] = g[i] - 2;
		if (rmin[i] < 0) rmin[i] = 0;

		rmax[i] = g[i] + 2;
		if (rmax[i] > n) rmax[i] = n;

		r[i] = a[i] = rmin[i];
	}

	for (rlog = -1;;) {
		for (i = 0, j = 0; i < 4; i++)
			j += a[i];

		if (j == n) {
			for (u = logf[n], i = 0; i < 4; i++)
				u += (double)a[i] * logc[i] - logf[a[i]];

			if (u > rlog)
				for (rlog = u, i = 0; i < 4; i++) r[i] = a[i];
		}

		for (i = 0; i < 4 && ++a[i] > rmax[i]; i++)
			a[i] = rmin[i];

		if (i == 4)
			break;
	}
printf("[%.10f] ",rlog);
}

int main()
{
	register int i, j;

	for (logf[0] = 0., i = 1; i < 350; i++)
		logf[i] = logf[i - 1] + log((double)i);

	while (scanf("%d %d %d %d %d", &n, &c[0], &c[1], &c[2], &c[3]) == 5) {
		if ((n | c[0] | c[1] | c[2] | c[3]) == 0)
			break;

		for (i = 0; i < 4; i++)
			logc[i] = log((double)c[i]);

		look();

		for (i = 0; i < 4; i++)
			printf(" %c=%d", 'i'+i, r[i]);
		printf("\n");
	}

	return 0;
}
