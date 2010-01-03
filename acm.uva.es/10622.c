#include <stdio.h>
#include <stdlib.h>

static unsigned long gcd(unsigned long a, unsigned long b)
{
	register unsigned long t;

	if (a > b) {
		t = a;
		a = b;
		b = t;
	}

	while (b > 0) {
		t = b;
		b = a % b;
		a = t;
	}

	return a;
}

/* Finds Floor[Sqrt[a]] */
static unsigned long int_sqrt(unsigned long a)
{
	register unsigned long x, y;
	for (x = a; ; x = y) {
		if (x <= 0) return 0;
		y = (x + (a / x)) >> 1;
		if (y >= x) return x;
	}
}

/* Finds GCD of powers of prime divisors in factorization of 'x' */
static int perfect(unsigned long x)
{
	unsigned long i, k, m, p;

	m = int_sqrt(x) + 4;
	for (i = 2, p = 0; i < m && x > 1; i += 2) {
		for (k = 0; (x % i) == 0; x /= i, k++);

		if (k != 0) {
			p = (p == 0) ? k : gcd(p, k);
			m = int_sqrt(x) + 4;
		}

		if (i == 2) i--;
	}

	if (x > 1 || p == 0)
		p = 1;

	return (int)p;
}

/* Extends perfect() with support for signed numbers */
static int perfect_signed(int x)
{
	if (x < 0) {
		int p = perfect((unsigned long)(-x));

		while (((p & 1) == 0) && p > 0)
			p >>= 1;
		if (p == 0) p = 1;

		return p;
	} else {
		return perfect((unsigned long)x);
	}
}

int main(void)
{
	int x;

	while (scanf("%d", &x) == 1 && x != 0)
		printf("%d\n", perfect_signed(x));

	return 0;
}
