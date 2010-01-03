#include <stdio.h>

int f(int e, int c, int t)
{
	if (t > 0)
		return f(e, c, 0) + 6 * (c + e) * t + 3 * t * t - 3 * t + ((e == 0 && c == 0) ? 1 : 0);
	else if (e > 0)
		return f(0, c, 0) + 4 * c * e + 2 * e * e - 2 * e + ((c == 0) ? 1 : 0);
	else if (c > 0)
		return (c * c - c + 2);
	else
		return 1;
}

int main()
{
	int e, c, t;

	while (scanf("%d %d %d", &e, &c, &t) == 3)
		printf("%d\n", f(e, c, t));

	return 0;
}
