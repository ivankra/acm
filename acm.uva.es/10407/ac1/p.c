#include <stdio.h>

static int gcd(int a, int b)
{
	int k = 0;

	if (a < 0) a = -a;
	if (b < 0) b = -b;

	if (a != 0 && b != 0)
		while (((a | b) & 1) == 0) a >>= 1, b >>= 1, k++;

	for (;;) {
		if (a == 0) return b;
		if (b == 0) return a;

		while ((a & 1) == 0) a >>= 1;
		while ((b & 1) == 0) b >>= 1;

		if (a > b)
			a -= b;
		else
			b -= a;
	}
}

int main()
{
	int n, m, a, b;

	for (n = 0, m = 0; scanf("%d", &a) == 1;) {
		if (a == 0) {
			if (n == 0) break;
			printf("%d\n", m);
			n = 0;
		} else if (n == 0) {
			n = 1;
			m = a;
			b = a;
		} else {
			if (n++ == 1)
				m = (a > b) ? (a - b) : (b - a);
			else
				m = gcd(m, (a > b) ? (a - b) : (b - a));
			b = a;
		}
	}

	return 0;
}
