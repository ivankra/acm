#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DELTA	1e-8

double px[1024], py[1024], x[1024], y[1024], ax, ay, bx, by;
int n;

int on_edge(double p)
{
	int i;

	for (i = 0; i < n; i++) {
		if (!(fabs(y[i]) < DELTA) || !(fabs(y[i + 1]) < DELTA))
			continue;

		if ((x[i] - 1e-12) <= p && p <= (x[i + 1] + 1e-12))
			return 1;

		if ((x[i + 1] - 1e-12) <= p && p <= (x[i] + 1e-12))
			return 1;
	}

	return 0;
}

double solve()
{
	static double c[1024], u, v, t;
	int i, j, k;

	bx -= ax;
	by -= ay;
	if ((bx*bx+by*by) < 1e-8) {for(;;)malloc(1000000);}

	t = sqrt(bx * bx + by * by);
	u = bx / t;
	v = -by / t;
/*printf("B=(%.5f, %.5f)  |B|=%.5f  cos=%.5f sin=%.5f\n", bx, by, t, u, v);*/

	for (i = 0; i < n; i++) {
		x[i] = (px[i] - ax) * u + (ay - py[i]) * v;
		y[i] = (px[i] - ax) * v + (py[i] - ay) * u;
	}

	x[n] = x[0];
	y[n] = y[0];
/*printf("Transformed:");for(i=0;i<n;i++)printf(" (%.3f,%.3f)",x[i],y[i]);printf("\n");
*/
	for (k = 0, i = 0; i < n; i++) {
		if ((fabs(y[i]) < DELTA) && (fabs(y[i + 1]) < DELTA)) {
			c[k++] = x[i];
			c[k++] = x[i + 1];
		} else if (fabs(y[i]) < DELTA) {
			if (y[i + 1] > 0) c[k++] = x[i];
		} else if (fabs(y[i + 1]) < DELTA) {
			if (y[i] > 0) c[k++] = x[i + 1];
		} else if ((y[i] * y[i + 1]) < 0) {
			c[k++] = x[i] - y[i] * (x[i + 1] - x[i]) / (y[i + 1] - y[i]);
		}
	}

	for (i = 1; i < k; i++) {
		for (t = c[i], j = i - 1; j >= 0 && c[j] > t; j--)
			c[j + 1] = c[j];
		c[j + 1] = t;
	}

/*printf("k=%d c=",k);for(i=0;i<k;i++)printf(" %.2f%s ",c[i],((i+1)>=k || !on_edge((c[i + 1] + c[i]) / 2.))?"" : " #");printf("\n");
*/
	for (t = 0, i = 0, j = 1; (i + 1) < k; i++, j ^= 1)
		if (j || on_edge((c[i + 1] + c[i]) / 2.))
			t += c[i + 1] - c[i];

	return t;
}

int main()
{
	int i, m;

	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		for (i = 0; i < n; i++)
			scanf("%lf %lf", &px[i], &py[i]);

		while (m-- > 0 && scanf("%lf %lf %lf %lf", &ax, &ay, &bx, &by) == 4)
			printf("%.3f\n", solve());
	}

	return 0;
}
