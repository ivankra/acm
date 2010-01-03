#include <stdio.h>

typedef unsigned long long num_t;

num_t root(num_t a, int n)
{
	num_t x, y;
	int i;

	for (x = a; x > (num_t)1; x = y) {
		for (y = a, i = 1; i < n; i++)
			y /= x;

		y = (y + x * (num_t)(n - 1)) / (num_t)n;

		if (y >= x)
			return x;
	}

	return x;
}

num_t power(num_t x, int e)
{
	num_t r;

	for (r = 1; e > 0; e >>= 1) {
		if (e & 1)
			r *= x;
		x *= x;
	}

	return r;
}

int main()
{
	unsigned h, w, n, k, i;
	num_t r;

	while (scanf("%u %u", &h, &w) == 2 && (h | w) != 0) {
		if (h == 1 && w == 1) {
			n = 1;
			k = 0;
		} else if (h == (w + 1)) {
			n = w;
			k = 1;
		} else {
			for (k = 2; k <= 32; k++) {
				n = (int)root((num_t)w, k);
				if (power((num_t)n, k) != (num_t)w) continue;

				i = (int)root((num_t)h, k);
				if (i != (n + 1)) continue;
				if (power((num_t)i, k) != (num_t)h) continue;

				break;
			}

			/*if (k > 32) ;*/
		}

		for (r = 0, i = 0; i < k; i++)
			r += power(n, i);
		printf("%lld ", (long long)r);

		for (r = 0, i = 0; i <= k; i++)
			r += power(n, k - i) * power(n + 1, i);
		printf("%lld\n", (long long)r);
	}

	return 0;
}
