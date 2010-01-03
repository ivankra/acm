#include <stdio.h>

static unsigned long a[16384];

int main()
{
	int n, i;
	unsigned long t;

	for (n=0;;) {
		if (scanf("%u", &t) < 1)
			break;

		for (i = n - 1; i >= 0 && a[i] > t; i--)
			a[i + 1] = a[i];

		a[i + 1] = t;
		n++;

		if (n < 2 || (n & 1) != 0) {
			printf("%u\n", a[n >> 1]);
		} else {
			t = (a[n >> 1] + a[(n - 1) >> 1]) >> 1;
			printf("%u\n", t);
		}
	}

	return 0;
}
