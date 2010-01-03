#include <stdio.h>

char* solve()
{
	static char s[256];
	double a, b, x, y;
	int n;

	scanf("%d", &n);

	for (a = 1, b = 0; n-- > 0 && scanf("%lf %lf", &x, &y) == 2;) {
		if (x > 0) {
			b += x * y;
		} else {
			b += -x * y;
			a -= y;
		}
	}

	if (a < 1e-10)
		return "God! Save me";

	sprintf(s, "%.2f", b / a);
	return s;
}

int main()
{
	int c, t;

	for (scanf("%d", &t), c = 1; c <= t; c++)
		printf("Case %d: %s\n", c, solve());

	return 0;
}
