#include <stdio.h>
#include <math.h>

int main()
{
	static char s[1024];
	double r1, r2, pi;
	int t;

	gets(s) && sscanf(s, "%d", &t);
	pi = 2. * acos(0.);

	while (t-- > 0 && gets(s)) {
		if (sscanf(s, "%lf %lf", &r1, &r2) == 2)
			printf("%.4f\n", 2. * pi * r1 * r2);
		else
			printf("%.4f\n", pi * r1 * r1 / 8.);
	}

	return 0;
}
