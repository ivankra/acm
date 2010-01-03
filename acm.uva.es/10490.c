#include <stdio.h>

unsigned long long isqrt(unsigned long long n)
{
	unsigned long long x, y;

	for (x = n; x > 1; x = y) {
		y = ((x + (n / x)) >> 1);
		if (y >= x) return x;
	}

	return x;
}

unsigned long long sigma(unsigned long long num)
{
	static unsigned long long p[128], s, r, x;
	static int e[128], a[128], n;
	int i, j;

	x = num;

	if (x == 0 || (x & 1) != 0) {
		n = 0;
	} else {
		for (n = 1, p[0] = 2, e[0] = 0; (x & 1) == 0; x >>= 1)
			e[0]++;
	}

	r = isqrt(x) + 1;
	for (s = 3; s <= r; s += 2) {
		if ((x % s) != 0)
			continue;

		p[n] = s;
		for (e[n] = 0; (x % s) == 0; x /= s, e[n]++);

		n++;
		r = isqrt(x) + 1;
	}

	if (x > 1) {
		p[n] = x;
		e[n++] = 1;
	}

	for (i = 0; i < n; i++)
		a[i] = 0;

	for (r = 0;;) {
		for (s = 1, i = 0; i < n; i++)
			for (j = 0; j < a[i]; j++) s *= p[i];

		r += s;

		for (i = 0; i < n; i++) {
			if (++a[i] <= e[i])
				break;
			else
				a[i] = 0;
		}

		if (i >= n)
			break;
	}

	return r;
}

int main()
{
	int n;
	unsigned long long s, t;

	while (scanf("%d", &n) == 1 && n > 0) {
		t = (1ULL << (n - 1)) * ((1ULL << n) - 1ULL);
		s = sigma(t);

		if ((t + t) == s)
			printf("Perfect: %lld!\n", (long long)t);
		else if (sigma(n) == (n + 1LL))
			printf("Given number is prime. But, NO perfect number "
			       "is available.\n");
		else
			printf("Given number is NOT prime! NO perfect number "
			       "is available.\n");
	}

	return 0;
}
