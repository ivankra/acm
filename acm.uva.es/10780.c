#include <stdio.h>

int get(int n, int p)
{
	int r, q;

	for (r = 0, q = p; q <= n; q *= p)
		r += n / q;

	return r;
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int solve()
{
	int i, k, n, f, r;

	scanf("%d %d", &n, &f);

	for (i = 2, r = 0x7FFFFFFF; i <= 70; i++) {
		for (k = 0; (n % i) == 0; n /= i, k++);

		if (k != 0) {
			r = min(r, get(f, i) / k);
			if (r == 0) return 0;
		}
	}

	if (n > 1)
		r = min(r, get(f, n));

	return r;
}

int main()
{
	int c, r, t;

	for (scanf("%d", &t), c = 1; c <= t; c++) {
		printf("Case %d:\n", c);
		r = solve();
		printf(r ? "%d\n" : "Impossible to divide\n", r);
	}

	return 0;
}
