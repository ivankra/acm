#include <stdio.h>
#include <string.h>
#include <math.h>

struct {
	char name[128];
	double la, lo, sin_la, sin_lo, cos_la, cos_lo;
} c[128];

double pi = 3.141592653589793, rad = 6378;
char s[1024], t[1024];

int main()
{
	int i, j, n;
	double a;

	for (n = 0; scanf(" %s", c[n].name) == 1 && c[n].name[0] != '#'; n++) {
		scanf("%lf %lf", &c[n].la, &c[n].lo);
		c[n].la *= pi / 180.;
		c[n].lo *= pi / 180.;
		c[n].sin_la = sin(c[n].la);
		c[n].cos_la = cos(c[n].la);
		c[n].sin_lo = sin(c[n].lo);
		c[n].cos_lo = cos(c[n].lo);
	}

	while (scanf(" %s %s", s, t) == 2 && (s[0] != '#' || t[0] != '#')) {
		printf("%s - %s\n", s, t);

		for (i = 0; i < n && strcmp(c[i].name, s) != 0; i++);
		for (j = 0; j < n && strcmp(c[j].name, t) != 0; j++);

		if (i == n || j == n) {
			printf("Unknown\n");
			continue;
		}

		a = c[i].sin_la * c[j].sin_la;
		a += c[i].cos_la * c[i].cos_lo * c[j].cos_la * c[j].cos_lo;
		a += c[i].cos_la * c[i].sin_lo * c[j].cos_la * c[j].sin_lo;

		if (a > 1.) a = 1.;
		if (a < -1.) a = -1.;

		printf("%.0f km\n", acos(a) * rad);
	}

	return 0;
}
