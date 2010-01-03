#include <stdio.h>

typedef unsigned long long num;

num a[32], c[32], f[32];

num choose(num n, num k)
{
	num r, i;
	if (k > n) return 0;
	for (r = 1, i = 0; i < k; i++)
		r = (r * (n - i)) / (i + 1);
	return r;
}

void part(int k, int r, int n)
{
	if (r > 0) {
		a[k] = (k == 0) ? 1 : (a[k-1] + 1);
		for (; a[k] <= r && a[k] < n; a[k]++)
			for (c[k] = 1; (c[k] * a[k]) <= r; c[k]++)
				part(k+1, r - c[k] * a[k], n);
	} else {
		num t;
		for (t = 1; k--;)
			t *= choose(f[a[k]]+c[k]-1, c[k]);
		f[n] += t;
	}
}

int main()
{
	int n;

	for (f[1] = 1, n = 2; n <= 31; n++) {
		f[n] = 0;
		part(0, n, n);
	}

	while (scanf("%d", &n) == 1 && n > 0)
		printf("%llu\n", (n == 1) ? 1ULL : (2*f[n]));

	return 0;
}
