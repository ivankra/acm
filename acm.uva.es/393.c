#include <stdio.h>
#include <string.h>

#define EPS 1e-12

int nwalls, nvert;
double wallx[32], doory[32][4], vx[128], vy[128];

double hypot(double, double);

int check(int a, int b)
{
	double t, m;
	int i;

	if (vx[a] >= vx[b])
		return 0;

	m = (vy[b] - vy[a]) / (vx[b] - vx[a]);

	for (i = 0; i < nwalls; i++) {
		if (wallx[i] <= vx[a] || wallx[i] >= vx[b])
			continue;

		t = m * (wallx[i] - vx[a]) + vy[a];

		if (doory[i][0] <= (t + EPS) && (t - EPS) <= doory[i][1])
			continue;

		if (doory[i][2] <= (t + EPS) && (t - EPS) <= doory[i][3])
			continue;

		return 0;

	}

	return 1;
}

int main()
{
	static double d[128][128];
	int i, j, k;

	while (scanf("%d", &nwalls) == 1 && nwalls >= 0) {
		for (i = 0; i < nwalls; i++)
			scanf("%lf %lf %lf %lf %lf",
			      &wallx[i],
			      &doory[i][0], &doory[i][1],
			      &doory[i][2], &doory[i][3]);

		nvert = 2;
		vx[0] = 0; vy[0] = 5;
		vx[1] = 10; vy[1] = 5;

		for (i = 0; i < nwalls; i++) {
			for (j = 0; j < 4; j++) {
				vx[nvert] = wallx[i];
				vy[nvert] = doory[i][j];
				nvert++;
			}
		}

		for (i = 0; i < nvert; i++)
			for (j = 0; j < nvert; j++)
				if (check(i, j))
					d[i][j] = hypot(vx[j] - vx[i], vy[j] - vy[i]);
				else
					d[i][j] = 1. / 0.;

		for (k = 0; k < nvert; k++)
			for (i = 0; i < nvert; i++)
				for (j = 0; j < nvert; j++)
					if ((d[i][k] + d[k][j]) < d[i][j])
						d[i][j] = d[i][k] + d[k][j];

		printf("%.2f\n", d[0][1]);
	}

	return 0;
}
