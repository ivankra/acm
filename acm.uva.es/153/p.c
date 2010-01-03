#include <stdio.h>
#include <string.h>

typedef unsigned long long num_t;

static num_t gcd_odd(num_t x, num_t y)
{
	for (;;) {
		if (x == 0) return y;
		if (y == 0) return x;

		while ((x & 1) == 0) x >>= 1;
		while ((y & 1) == 0) y >>= 1;

		if (x > y)
			x -= y;
		else
			y -= x;
	}
}

static num_t count(char *s, int n)
{
	static int cnt[256];
	int i;
	num_t r, d, g;

	for (i = 'a'; i <= 'z'; i++) cnt[i] = 0;

	for (i = 1, r = 1, d = 1; i <= n; i++, s++) {
		r *= (num_t)i;
		d *= ++cnt[(unsigned)*s];

		while (((r | d) & 1) == 0) {
			r >>= 1;
			d >>= 1;
		}

		if (r > 0x1000000ULL) {
			g = gcd_odd(r, d);
			r /= g;
			d /= g;
		}
	}

	return r / d;
}

int main()
{
	static char str[1024];
	int i, j, k, n, p;
	num_t r;

	while (scanf(" %[a-z]", str) == 1) {
		for (n = 0; str[n]; n++);

		r = 0;
		for (p = 0; (p + 1) < n; p++) {
			for (i = 'a'; i < str[p]; i++) {
				for (j = p + 1; j < n; j++)
					if (str[j] == i) break;
				if (j >= n) continue;

				k = str[j];
				str[j] = str[p];

				r += count(str + p + 1, n - p - 1);

				str[j] = k;
			}
		}

		printf("%10lld\n", r+1);
	}

	return 0;
}
