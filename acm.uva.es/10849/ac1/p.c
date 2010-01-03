#include <stdio.h>

int abs(int x)
{
	return (x > 0) ? x : -x;
}

char *go(int y0, int x0, int y1, int x1, int n)
{
	if (((x0 + y0) & 1) != ((x1 + y1) & 1))
		return "no move";

	if (y0 == y1 && x0 == x1)
		return "0";

	if (abs(y1 - y0) == abs(x1 - x0))
		return "1";

	return "2";
}

int main()
{
	int x0, y0, x1, y1, n, s, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &s, &n) == 2;)
		while (s-- > 0 && scanf("%d %d %d %d", &y0, &x0, &y1, &x1) == 4)
			printf("%s\n", go(y0, x0, y1, x1, n));

	return 0;
}
