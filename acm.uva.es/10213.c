#include <stdio.h>

#define S 8

unsigned a[S];

int f(int n)
{
	return (n*n*n*n - 6*n*n*n + 23*n*n - 18*n + 24) / 24;
}

void mul(unsigned b)
{
	unsigned long long c;
	unsigned i;

	for (c = 0, i = 0; i < S; i++, c >>= 32) {
		c += (unsigned long long)a[i] * (unsigned long long)b;
		a[i] = (unsigned)(c & 0xFFFFFFFF);
	}
}

void add(long long c)
{
	unsigned i;
	for (i = 0; i < S && c != 0; i++) {
		c += (long long)a[i];
		if (c < 0) {
			c += 0x100000000LL;
			a[i] = (unsigned)(c & 0xFFFFFFFF);
			c = -1;
		} else {
			a[i] = (unsigned)(c & 0xFFFFFFFF);
			c >>= 32;
		}
	}
}

unsigned div(unsigned d)
{
	unsigned i;
	unsigned long long r;

	for (i = S, r = 0; i--;) {
		r = (r << 32) | (unsigned long long)a[i];
		a[i] = r / (unsigned long long)d;
		r %= (unsigned long long)d;
	}

	return (unsigned)r;
}

int iszero()
{
	int i;
	for (i = 0; i < S; i++)
		if (a[i] != 0) return 0;
	return 1;
}

int main()
{
	unsigned z[128], t, n;

	for (scanf("%u", &t); t-- && scanf("%u", &n) == 1;) {
		if (n <= 200) {
			printf("%d\n", f(n));
			continue;
		}

		a[0] = n - 6; a[1] = a[2] = a[3] = 0;
		mul(n); add(23); mul(n); add(-18); mul(n); add(24); div(24);

		for (n = 0; !iszero();)
			z[n++] = div(10);

		while (n--)
			putchar(z[n] + '0');
		putchar('\n');
	}

	return 0;
}
