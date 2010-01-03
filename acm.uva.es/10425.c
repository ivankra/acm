#include <stdio.h>
#include <assert.h>

#define s(a) ((a) * (a))

int main()
{
	long long x1, y1, z1, r1, x2, y2, z2, r2, x, y, z, u, v, t;
	char a[256];

	while (scanf(" %s", a) == 1) {
		scanf("%lld %lld %lld %lld", &x1, &y1, &z1, &r1);
		scanf("%lld %lld %lld %lld", &x2, &y2, &z2, &r2);
		scanf("%lld %lld %lld", &x, &y, &z);

		u = s(x - x1) + s(y - y1) + s(z - z1);
		v = s(x - x2) + s(y - y2) + s(z - z2);

		printf("%s\n%s\n%s\n",
			a, (u <= s(r1)) ? "y" : "n", (v <= s(r2)) ? "y" : "n");

		if (u > s(r1) && v > s(r2)) {
			printf("n\n");
			continue;
		}

		t = s(x1-x2) + s(y1-y2) + s(z1-z2) - s(r1+r2);

		if (t > 0) {
			printf("y\n");
			continue;
		}

		if (t == 0) {
			printf("y\n");
			continue;
		}

		t = (x-x1)*(x2-x1) + (y-y1)*(y2-y1) + (z-z1)*(z2-z1);
		t *= 2;
		t -= r1*r1 - r2*r2 + s(x1-x2) + s(y1-y2) + s(z1-z2);

		if (t == 0)
			printf("n\n");
		else
			printf("y\n");
	}

	return 0;
}
