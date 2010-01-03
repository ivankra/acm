#include <stdio.h>

int tab[512][512];

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int guess(int a, int b, int last)
{
	int k, s, r, ax, bx;

	if (a > b)
		return 0;

	if (a == b)
		return (a == last) ? 0 : 1;

	b -= a;
	last -= a;
	a = 0;

	last = min(last, b - last);

	if (last < 0)
		last = b - last;

	if (tab[b][last] >= 0)
		return tab[b][last];

	for (k = a, r = 0x3FFFFFFF; k <= b; k++) {
		if (k == last)
			continue;

		/* `W':
			|k - x| <= |last - x|

			k >= x >= last:
			(k + last) / 2 <= x

			k <= x <= last:
			x <= (k + last) / 2
		*/

		if (k > last) {
			ax = max(a, (k + last + 1) / 2);
			bx = b;
		} else {
			ax = a;
			bx = min(b, (k + last) / 2);
		}

		s = guess(ax, bx, k) + 1;


		/* `C':
			|k - x| >= |last - x|

			last <= x <= k:
			x <= (k + last) / 2

			k <= x <= last:
			(k + last) / 2 <= x
		*/

		if (last < k) {
			ax = a;
			bx = min(b, (k + last) / 2);
		} else {
			ax = max(a, (k + last + 1) / 2);
			bx = b;
		}

		s = max(s, guess(ax, bx, k) + 1);

		r = min(r, s);
	}

	return (tab[b][last] = r);
}

int solve(int n)
{
	int i, j;

	for (i = 1, j = 0x3FFFFFFF; i <= n; i++)
		j = min(j, guess(1, n, i) + 1);

	return j;
}

int main()
{
	int i, j, n;

	for (i = 0; i < 512; i++)
		for (j = 0; j < 512; j++)
			tab[i][j] = -1;

	while (scanf("%d", &n) == 1 && n > 0)
		printf("%d guess(es) required.\n", solve(n));

	return 0;
}
