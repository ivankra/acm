#include <stdio.h>
#include <string.h>

int tab[64][64], binom[64][64], fact[64];

int f(int n, int a)
{
	int s, k;

	if (n < 0 || a < 0)
		return 0;

	if (n == 0)
		return (a == 0) ? 1 : 0;

	if (tab[n][a] >= 0)
		return tab[n][a];

	for (s = 0, k = 1; k <= n; k++)
		s += binom[n - 1][k - 1] * fact[n - k] * f(k - 1, a - 1);

	return (tab[n][a] = s);
}

int solve(int n, int a, int b)
{
	int s, k;

	if (n < 0 || a < 0 || b < 0 || a > n || b > n)
		return 0;

	for (s = 0, k = 1; k <= n; k++)
		s += binom[n - 1][n - k] * f(k - 1, a - 1) * f(n - k, b - 1);

	return s;
}

int main()
{
	int a, b, n, t;

	memset(binom, 0, sizeof(binom));
	for (n = 0; n < 64; n++)
		for (binom[n][0] = 1, a = 1; a <= n; a++)
			binom[n][a] = binom[n - 1][a - 1] + binom[n - 1][a];

	for (a = 0; a < 64; a++)
		for (b = 0; b < 64; b++)
			tab[a][b] = -1;

	for (fact[0] = 1, n = 1; n < 64; n++)
		fact[n] = n * fact[n - 1];

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d %d", &n, &a, &b) == 3;)
		printf("%d\n", solve(n, a, b));

	return 0;
}
