#include <stdio.h>
#include <string.h>
#include <math.h>

#define PI 669

int primes[PI], primelog[PI], factp[5002][PI], factk[5002], data[PI];
unsigned num[12];

static void nummul(unsigned m)
{
	unsigned long long c;
	int i;

	for (i = 0, c = 0; i < 12; i++)  {
		c += (unsigned long long)num[i] * (unsigned long long)m;
		num[i] = (unsigned long)(c);
		c >>= 32;
	}
}


static void numeval()
{
	unsigned long m;
	int i;

	memset(num, '\0', sizeof(num));
	num[0] = 1;

	for (i = 0, m = 1; i < PI; i++) {
		while (data[i]-- > 0) {
			m *= primes[i];
			if (m >= 0xFFFFF) {
				nummul(m);
				m = 1;
			}
		}
	}

	if (m != 1)
		nummul(m);
}

static void numprint()
{
	static char buf1[1024], buf2[1024];
	unsigned long long c;
	int i, k, r;

	for (k = 0;;) {
		for (i = 0; i < 12; i++)
			if (num[i] != 0) break;
		if (i >= 12) break;

		for (i = 11, c = 0; i >= 0; i--) {
			c = (c << 32) | (unsigned long long)num[i];
			num[i] = (unsigned)(c / 1000000000ULL);
			c %= 1000000000ULL;
		}

		for (r = (unsigned)c, i = 0; i < 9; i++, r /= 10)
			buf1[k++] = (r % 10) + '0';
	}

	while (k > 1 && buf1[k - 1] == '0')
		k--;

	if (k > 100) {
		printf("-1\n");
		return;
	}

	for (i = 0; k-- > 0;)
		buf2[i++] = buf1[k];
	buf2[i] = '\0';

	printf("%s\n", buf2);
}

static void mkprimes()
{
	static char sieve[5000];
	int i, j, n;

	memset(sieve, '\0', sizeof(sieve));

	for (n = 0, i = 2; i < 5000; i++) {
		if (sieve[i])
			continue;

		primes[n++] = i;

		for (j = i * i; j < 5000; j += i)
			sieve[j] = 1;
	}

	for (i = 0; i < n; i++)
		primelog[i] = log10((double)primes[i]);
}

static void mkfact()
{
	int i, k, t, n;

	memset(factp, '\0', sizeof(factp));
	factk[0] = factk[1] = 0;

	for (n = 1; n <= 5000; n++) {
		for (t = n, k = 0; k < factk[n]; k++) {
			while ((t % primes[k]) == 0) {
				factp[n][k]++;
				t /= primes[k];
			}
		}

		if (t > 1) {
			factp[n][k++] = 1;
			factk[n] = k;
		}

		for (i = 0; i < k; i++)
			factp[n + 1][i] = factp[n][i];
		factk[n + 1] = k;
	}
}

static void mul(int n)
{
	register int k, *p, *q;

	k = factk[n];
	p = factp[n];
	q = data;

	while (k-- > 0)
		*q++ += *p++;
}

static void div(int n)
{
	register int k, *p, *q;

	k = factk[n];
	p = factp[n];
	q = data;

	while (k-- > 0)
		*q++ -= *p++;
}

int main()
{
	int a, b, i, n1, n2;
	double lg;

	mkprimes();
	mkfact();

	while (scanf("%d %d", &n1, &n2) == 2) {
		memset(data, '\0', sizeof(data));

		while (n1-- > 0 && scanf("%d %d", &a, &b) == 2) {
			mul(a);
			div(b);
			div(a - b);
		}

		while (n2-- > 0 && scanf("%d %d", &a, &b) == 2) {
			div(a);
			mul(b);
			mul(a - b);
		}

		for (i = 0; i < PI; i++)
			if (data[i] < 0) break;

		if (i < PI) {
			printf("0\n");
			continue;
		}

		for (i = 0, lg = 0.; i < PI; i++)
			if (data[i] != 0) lg += primelog[i] * (double)data[i];

		if (lg > 100.1) {
			printf("-1\n");
			continue;
		}

		numeval();
		numprint();
	}

	return 0;
}
