#include <stdio.h>

unsigned cvt1(int x)
{
	return (x < 0) ? (1 + ~(unsigned)(-x)) : (unsigned)x;
}

int cvt2(unsigned x)
{
	return (x & 0x80000000) ? -(1 + ~x) : x;
}

int main()
{
	static unsigned a[16384];
	int i, n, k, x;

	while (scanf("%d %d", &n, &k) == 2 && n >= 0) {
		for (i = 0; i <= n && scanf("%d", &x) == 1; i++)
			a[i] = cvt1(x);

		for (; n >= k; n--)
			a[n - k] -= a[n];

		if (n < 0) {
			printf("0\n");
		} else {
			while (n > 0 && a[n] == 0) n--;
			for (i = 0; i <= n; i++)
				printf((i < n) ? "%d " : "%d\n", cvt2(a[i]));
		}
	}

	return 0;
}
