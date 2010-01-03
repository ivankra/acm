#include <stdio.h>
#include <math.h>

#define MAXN 65536

struct {
	double x, c;
	int g, y, r;
} z[MAXN];

int n;

int test(int v)
{
	int i;
	double t;

	for (i = 0; i < n; i++) {
		t = fmod(z[i].x * 3600.0 / (double)v, z[i].c);

		if (t > (z[i].c - 1e-12))
			continue;

		if (t < (double)(z[i].g + z[i].y + 1e-12))
			continue;

		return 0;
	}

	return 1;
}

int main()
{
	int i, k, m, t;

	for (t = 1; scanf("%d", &n) == 1 && n >= 0; t++) {
		for (i = 0; i < n; i++) {
			scanf("%lf %d %d %d", &z[i].x, &z[i].g, &z[i].y, &z[i].r);
			z[i].c = (double)(z[i].g + z[i].y + z[i].r);
		}
		printf("Case %d:", t);

		for (k = 0, m = 0, i = 30; i <= 61; i++) {
			if (i <= 60 && test(i)) {
				m++;
			} else if (m > 0) {
				printf(k++ ? ", " : " ");
				printf((m == 1) ? "%d" : "%d-%d", i - m, i - 1);
				m = 0;
			}
		}

		printf(k ? "\n" : " No acceptable speeds.\n");
	}

	return 0;
}
