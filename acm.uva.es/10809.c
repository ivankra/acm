#include <stdio.h>
#include <math.h>

#define EPS 1e-8

typedef struct {
	double x, y, z;
} vec;

double pi;

vec get()
{
	double la, lo;
	char s[16];
	int a, b;
	vec v;

	scanf("%d,%d %s", &a, &b, s);
	la = ((a + b / 60.) * pi / 180.) * ((s[0] == 'N') ? 1. : -1.);

	scanf("%d,%d %s", &a, &b, s);
	lo = ((a + b / 60.) * pi / 180.) * ((s[0] == 'E') ? 1. : -1.);

	v.x = cos(la) * cos(lo);
	v.y = cos(la) * sin(lo);
	v.z = sin(la);

	return v;
}

int main()
{
	int i, n;
	vec a, b;
	double r, t, u, v;

	pi = 2 * acos(0);

	for (scanf("%d", &n); n-- > 0;) {
		a = get();
		b = get();

		t = a.x * b.x + a.y * b.y + a.z * b.z;

		if (fabs(t + 1) < EPS) {
			if (fabs(a.z - 1) < EPS || fabs(b.z - 1) < EPS)
				printf("90,0N\n");
			else
				printf("undefined\n");
			continue;
		}

		r = (a.z > b.z) ? a.z : b.z;
		u = (b.z - t * a.z) / sqrt(1. - t * t);

		for (i = -2; i <= 2; i++) {
			v = atan(u / a.z) + i * pi;
			while (v < -EPS) v += 2 * pi;
			while (v > (2 * pi - EPS)) v -= 2 * pi;

			if (-EPS < v && v < (pi + EPS) &&
			    (t - EPS) < cos(v) && cos(v) < (1. + EPS)) {
				v = a.z * cos(v) + u * sin(v);
				if (v > r) r = v;
			}
		}

		r = asin(r) * 180. * 60. / pi;

		if (fabs(ceil(r) - r) < fabs(r - floor(r)))
			i = (int)ceil(r);
		else
			i = (int)floor(r);

		if (i < 0) {
			i = -i;
			printf("%d,%dS\n", i / 60, i % 60);
		} else {
			printf("%d,%dN\n", i / 60, i % 60);
		}
	}

	return 0;
}
