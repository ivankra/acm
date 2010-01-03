#include <stdio.h>
#include <stdlib.h>

static void print64(long long x)
{
	static char buf[32];
	int i;
	for (i = 0; x > 0; x /= 10) buf[i++] = '0' + (x % 10);
	printf("    ");
	while (i-- > 0) putchar(buf[i]);
	printf("\n");
}

static long long int_sqrt(long long n)
{
	register long long x, y;
	for (x = n;;) {
		if (x < 1) return 1;
		y = (x + (n / x)) >> (long long)1;
		if (y >= x) return x;
		x = y;
	}
}

static void factor(long long x)
{
	long long d, m;
	int i, k, s;

	if (x <= 3) {
		print64(x);
		return;
	}

	m = int_sqrt(x) + 10;
	if (m > x) m = x;

	for (d = 2, s = -1; x > 1 && d < m;) {
		for (k = 0; (x % d) == 0; x /= d, k++);

		if (k > 0) {
			for (i = 0; i < k; i++)
				print64(d);
			m = int_sqrt(x) + 10;
			if (m > x) m = x;
		}

		if (s == 0) {
			d += 2;
			s = 1;
		} else if (s == 1) {
			d += 4;
			s = 0;
		} else {
			if (d == 2) {
				d = 3;
			} else if (d == 3) {
				d = 5;
				s = 0;
			}
		}
	}

	if (x > 1)
		print64(x);
}

int main()
{
	long long x;
	int c;

	for (;;) {
		while ((c = getchar()) != EOF)
			if (c == '-' || (c >= '0' && c <= '9')) break;
		if (c == '-' || c == EOF) break;

		for (x = 0;;) {
			x = x * 10 + c - '0';
			if ((c = getchar()) == EOF) break;
			if (c < '0' || c > '9') break;
		}

		factor(x);
		printf("\n");
	}

	return 0;
}
