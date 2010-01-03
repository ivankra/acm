#include <stdlib.h>

int read(int, char *, int);
int write(int, char *, int);

static unsigned isqrt(unsigned a)
{
	unsigned x, y;

	for (x = a; x > 1; x = y)
		if ((y = (x + (a / x)) >> 1) >= x) break;

	return x;
}

static unsigned factorize(unsigned e[], unsigned x)
{
	unsigned i, m, n = 0;

	if (x == 0)
		return 0;

	if ((x & 1) == 0) {
		for (e[n] = 0; (x & 1) == 0; x >>= 1) e[n]++;
		n++;
	}

	for (i = 3, m = isqrt(x) + 1; i <= m; i += 2) {
		if ((x % i) == 0) {
			for (e[n] = 1, x /= i; (x % i) == 0; e[n]++)
				x /= i;
			n++;
			m = isqrt(x);
		}
	}

	if (x > 1)
		e[n] = 1, n++;

	return n;
}

static unsigned solve(unsigned x)
{
	static unsigned a[128], e[128], n;
	unsigned i, r, t;

	n = factorize(e, x);

	for (i = 0; i <= n; i++) a[i] = 0;

	for (r = 0;;) {
		for (t = 1, i = 0; i < n; i++)
			if (a[i] == e[i]) t *= (e[i] + 1);
		r += t;

		for (i = 0; i < n; i++)
			if (++a[i] <= e[i])
				break;
			else
				a[i] = 0;
		if (i >= n) break;
	}

	return (r + 1) >> 1;
}

int main2()
{
	static char inbuf[65536], outbuf[65536], tmp[256];
	static int isdig[256];
	char *p, *q, *s;
	unsigned n;

	for (n = '0'; n <= '9'; n++) isdig[n] = 1;

	read(0, p = inbuf, sizeof(inbuf));
	q = outbuf;

	for (;;) {
		while (!isdig[*p]) p++;

		s = p;
		for (n = *p++ - '0'; isdig[*p];) n = n * 10 + *p++ - '0';
		if (n == 0) break;

		while (s < p) *q++ = *s++;
		*q++ = ' ';

		n = solve(n);
		for (s = tmp; n > 0; n /= 10) *s++ = (n % 10) + '0';
		while (s-- > tmp) *q++ = *s;
		*q++ = '\n';
	}

	write(1, outbuf, q - outbuf);
	exit(0);
}
