#include <stdio.h>

int isqrt(int a)
{
	int x, y;

	for (x = a; x > 1; x = y) {
		y = (x + a / x) >> 1;
		if (y >= x) break;
	}

	return x;
}

int main()
{
	int i, n, k, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &k) == 1;) {
		if (k < 0) k = -k;

		for (i = 1, n = 1; i < k; n++)
			i += (n + 1);

		while (("0110"[n & 3] - '0') != (k & 1))
			n++;

		printf(t ? "%d\n\n" : "%d\n", n);
	}

	return 0;
}
