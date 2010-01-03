#include <stdio.h>
#include <string.h>

int tab[1024][1024], n;
char s[1024];

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int f(int a, int b)
{
	if (tab[a][b] >= 0)
		return tab[a][b];

	if ((b - a) <= 0)
		return (tab[a][b] = 0);

	if (s[a] == s[b])
		return (tab[a][b] = f(a + 1, b - 1));

	tab[a][b] = min(f(a + 1, b), min(f(a, b - 1), f(a + 1, b - 1))) + 1;
	return tab[a][b];
}

int main()
{
	int i, j, c, t;

	for (scanf("%d", &t), c = 1; c <= t && scanf(" %s", s) == 1; c++) {
		for (n = strlen(s), i = 0; i < n; i++)
			for (j = i; j < n; j++) tab[i][j] = -1;
		printf("Case %d: %d\n", c, f(0, n - 1));
	}

	return 0;
}
