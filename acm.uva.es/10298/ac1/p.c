#include <stdio.h>

static int isqrt(int a)
{
	register int x, y;

	for (x = a; x > 0; x = y)
		if ((y = (x + (a / x)) >> 1) >= x) return x;

	return 0;
}

static int divisors(int n, int r[])
{
	static int b[16], p[16], a[16];
	int i, j, k, m;

	if (n & 1)
		k = 0;
	else
		for (k = 1, b[0] = 2, p[0] = 0; (n & 1) == 0; n >>= 1, p[0]++);

	m = isqrt(n) + 1;
	for (i = 3; i <= m; i += 2)
		if ((n % i) == 0) {
			for (n /= i, b[k] = i, p[k] = 1; (n % i) == 0; n /= i)
				p[k]++;

			k++;
			if (n <= 1)
				break;

			m = isqrt(n) + 1;
		}

	if (n > 1) {
		b[k] = n;
		p[k++] = 1;
	}

	for (i = 0; i < k; i++)
		a[i] = 0;

	for (m = 0;;) {
		for (r[m] = 1, i = 0; i < k; i++)
			for (j = 0; j < a[i]; j++) r[m] *= b[i];

		for (m++, i = 0;; i++) {
			if (i >= k)
				return m;
			else if (++a[i] <= p[i])
				break;
			else
				a[i] = 0;
		}
	}
}

static void sort(int a[], int n)
{
	register int i, j, t;

	for (i = 1; i < n; i++) {
		for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
			a[j + 1] = a[j];
		a[j + 1] = t;
	}
}

int main()
{
	static char s[1048576];
	static int d[256], c, p, n;
	register int i, j, k;

	while (fgets(s, sizeof(s), stdin) != NULL) {
		for (i = 0; s[i] != '\0' && s[i] != '\n'; i++);
		s[i] = '\0';
		n = i;

		if (n == 0)
			continue;

		if (n == 1 && s[0] == '.')
			break;

		c = divisors(n, d);
		sort(d, c);

		for (p = 0, k = 1; p < c; p++) {
			k = d[p];

			for (i = 0, j = 0; i < n; i++) {
				if (s[i] != s[j])
					break;

				if (++j >= k)
					j = 0;
			}

			if (i == n)
				break;
		}

		printf("%d\n", n / k);
	}

	return 0;
}
