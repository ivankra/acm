#include <cstdio>
#include <cmath>
#include <cassert>

int modexp(int b, int e, int m) {
	int r = 1;
	b %= m;
	for (; e > 0; e >>= 1) {
		if (e & 1) r = (r * b) % m;
		b = (b * b) % m;
	}
	return r % m;
}

int main()
{
	unsigned n, k;
	int T;
	for (scanf("%d", &T); T-- > 0 && scanf("%u %u", &n, &k) == 2;) {
		assert(n > 0 && k > 0);

		long double l = log10((long double)n) * k;
		long double x = pow(10.0L, l - (floor(l+1e-6) - 10));
		char s[256];
		sprintf(s, "%.5Lf", x);

		printf("%.3s...%.3d\n", s, modexp(n%1000, k, 1000));
	}
}
