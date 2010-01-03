#include <stdio.h>

/* Let G(n) be a tree on n vertices, with out-degree of each its
   vertex limited to {0,2} */

/* Returns the number of different G(n) trees */
int g(int n)
{
	int s, k;

	if (n == 0 || n == 1)
		return 1;

	if (n < 0 || ((n % 2) == 0))
		return 0;

	for (s = 0, k = 0; k < n; k++)
		s += g(k) * g(n - k - 1);

	return s;
}

/* Returns the number of ordered forests of G(i) trees on m vertices */
int f(int m)
{
	int s, k;

	if (m < 0)
		return 0;

	if (m == 0)
		return 1;

	for (s = 0, k = 1; k <= m; k++)
		s += g(k) * f(m - k);

	return s;
}

int main()
{
	int n;

	while (scanf("%d", &n) == 1)
		printf("f(%d) = %d, g(%d) = %d\n", n, f(n), n, g(n));

	return 0;
}
