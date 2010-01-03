#include <stdio.h>

int tab[512][512];

int f(int n, int k)
{
	int i, s;

	if (n <= 1)
		return 0;

	if (tab[n][k] >= 0)
		return tab[n][k];

	for (i = 1; i <= n; i++) {
		s = n * (k + i) + f(i - 1, k) + f(n - i, k + i);

		if (i == 1 || s < tab[n][k])
			tab[n][k] = s;
	}

	return tab[n][k];
}

int main()
{
	int c, n, k, t;

	for (n = 0; n <= 500; n++)
		for (k = 0; k <= 500; k++)
			tab[n][k] = -1;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d %d", &n, &k) == 2; c++)
		printf("Case %d: %d\n", c, f(n, k));

	return 0;
}
