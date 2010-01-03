#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

static void sort(long long a[], int n)
{
	int i, j;
	long long p, t;

re:	if (n < 16) {
		for (i = 1; i < n; i++) {
			for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}
		return;
	}

	for (i = -1, j = n, p = a[n >> 1];;) {
		while (a[++i] < p);
		while (a[--j] > p);
		if (i >= j) break;
		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	if ((i + 1) < n)
		sort(a + i, n - i);

	n = i;
	goto re;
}

static int find(long long v[], int n, long long x)
{
	register int a, b, c;

	for (a = 0, b = n - 1; a < b;) {
		c = (a + b) >> 1;

		if (v[c] == x)
			a = b = c;
		else if (v[c] > x)
			b = c - 1;
		else
			a = c + 1;
	}

	c = (c < 5) ? 0 : (c - 5);
	while (c < n && v[c] < x) c++;

	return c;
}

int main()
{
	static unsigned char sieve[126000];
	static long long a[85000];
	long long x, y, t;
	int i, j, m, n;

	memset(sieve, '\0', sizeof(sieve));
	for (i = 2, m = 0; i < 1000000; i = (i == 2) ? 3 : (i + 2)) {
		if (i > 2) {
			if ((sieve[i >> 3] >> (i & 7)) & 1)
				continue;

			for (j = i; j < 1000000; j += i)
				sieve[j >> 3] |= 1 << (j & 7);
		}

		if (i < 10200) {
			x = (long long)i * (long long)i;
			for (; x < 1000000000000ULL; x *= (long long)i)
				a[m++] = x;
		} else {
			a[m++] = (long long)i * (long long)i;
		}
	}

	sort(a, m);

	scanf("%d", &n);
	while (n-- > 0) {
		while ((j = getchar()) != EOF && !isdigit(j));
		for (x = 0; j != EOF && isdigit(j); j = getchar())
			x = x * 10 + j - '0';

		while ((j = getchar()) != EOF && !isdigit(j));
		for (y = 0; j != EOF && isdigit(j); j = getchar())
			y = y * 10 + j - '0';

		if (x > y) { t = x; x = y; y = t; }

		printf("%d\n", find(a, m, y + 1) - find(a, m, x));
	}

	return 0;
}
