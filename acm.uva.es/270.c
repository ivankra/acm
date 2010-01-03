#include <stdio.h>
#include <stdlib.h>

static int x[1024], y[1024], n;

static void sort(unsigned a[], int n)
{
	int i, j;
	unsigned p, t;

re:	if (n <= 32) {
		for (i = 1; i < n; i++) {
			for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}
		return;
	}

	for (p = a[(n - 1) >> 1], i = -1, j = n;;) {
		while (a[++i] < p);
		while (a[--j] > p);

		if (i >= j)
			break;

		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	if ((n - i) > 1)
		sort(a + i, n - i);

	n = i;
	goto re;
}


static int gcd(int x, int y)
{
	if (x < 0) x = -x;
	if (y < 0) y = -y;

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

static int solve()
{
	static unsigned s[4096];
	static int r;
	int i, j, k, a, b;

	if (n <= 2)
		return n;

	for (k = 0, r = 2; k < n; k++) {
		for (i = 0; i < n; i++) {
			if (i == k) {
				s[i] = 0x00000000;
			} else if (y[i] == y[k]) {
				s[i] = 0x00000001;
			} else if (x[i] == x[k]) {
				s[i] = 0x00010000;
			} else {
				a = y[i] - y[k];
				b = x[i] - x[k];

				if (b < 0) {
					a = -a;
					b = -b;
				}

				while (((a | b) & 1) == 0) {
					a >>= 1;
					b >>= 1;
				}

				j = gcd(a, b);
				a /= j;
				b /= j;

				s[i] = ((((unsigned long)a) & 0xFFFF) << 16) |
				        (((unsigned long)b) & 0xFFFF);
			}
		}

		sort(s, n);		

		for (i = 0; i < n; i = j) {
			for (j = i + 1; j < n && s[j] == s[i]; j++);

			if ((j - i + 1) > r)
				r = j - i + 1;
		}
	}

	return r;
}

int main()
{
	char s[256];
	int t;

	for (scanf("%d", &t); t-- > 0;) {
		for (n = 0; gets(s);) {
			if (sscanf(s, "%d %d", &x[n], &y[n]) == 2)
				n++;
			else if (n != 0)
				break;
		}

		printf(t ? "%d\n\n" : "%d\n", solve());
	}

	return 0;
}
