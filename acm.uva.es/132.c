#include <stdio.h>

#define MAXN 131072

int x[MAXN], y[MAXN], n;

int check(int a, int b)
{
	int i, k, c1, c2;

	if ((x[a] == 0 && y[a] == 0) || (x[b] == 0 && y[b] == 0))
		return 0;

	if (x[a] == x[b] && y[a] == y[b])
		return 0;

	k = x[a] * (x[b] - x[a]) + y[a] * (y[b] - y[a]);
	k *= x[b] * (x[a] - x[b]) + y[b] * (y[a] - y[b]);
	if (k <= 0)
		return 0;

	for (c1 = c2 = 0, i = 0; i < n; i++) {
		k = (x[b] - x[a]) * (y[i] - y[a]) - (x[i] - x[a]) * (y[b] - y[a]);

		if (k == 0 && (i > a || i < b))
			return 0;

		if (k < 0)
			c1++;
		else if (k > 0)
			c2++;
	}

	return (c1 == 0 || c2 == 0);
}

int solve()
{
	int a, b;

	for (a = 1; a < n; a++)
		for (b = 0; b < a; b++)
			if (check(a, b)) return (a + 1);

	return 1;
}

int main()
{
	static char s[256];
	int cx, cy;

	while (scanf(" %[^\n] %d %d", s, &cx, &cy) == 3 && s[0] != '#') {
		for (n = 0; scanf("%d %d", &x[n], &y[n]) == 2 && (x[n] | y[n]); n++)
			x[n] -= cx, y[n] -= cy;

		printf("%-20s%d\n", s, solve());
	}

	return 0;
}
