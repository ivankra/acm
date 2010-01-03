#include <stdio.h>
#include <math.h>

int get(int n, int p)
{
	int r, q;

	for (r = 0, q = p; q <= n; q *= p)
		r += (n / q);

	return r;
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int z(int n, int b)
{
	int e, p, r;

	for (p = 2, r = 0x3FFFFFFF; p <= b; p++) {
		for (e = 0; (b % p) == 0; b /= p, e++);

		if (e == 0)
			continue;

		r = min(r, get(n, p) / e);
	}

	return r;
}

int main()
{
	static double s[1048576], u;
	int i, n, b;

	for (s[0] = 0, i = 1; i < 1048576; i++)
		s[i] = s[i - 1] + log(i);

	while (scanf("%d %d", &n, &b) == 2) {
		printf("%d ", z(n, b));

		u = s[n] / log(b);
		if ((ceil(u) - u) < 1e-14)
			printf("%.0f\n", ceil(u) + 1);
		else
			printf("%.0f\n", floor(u) + 1);
	}

	return 0;
}
