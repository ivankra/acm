#include <stdio.h>
#include <string.h>

static int f(unsigned long x)
{
	register unsigned long n;
	register int k;

	for (k = 0, n = x;;) {
		if (n & 1) {
			n = 3 * (n >> 1) + 2;
			k += 2;
		} else {
			k++;
			if ((n >>= 1) <= 1)
				return k;
		}
	}
}

int main()
{
	static unsigned long mx, mr, a, b;
	unsigned long i, r;

	while (scanf("%u%u", &a, &b) == 2 && (a != 0 || b != 0)) {
		if (a > b) {
			i = a;
			a = b;
			b = i;
		}

		for (i = a, mr = mx = 0; i <= b; i++) {
			r = f(i);

			if (r > mr) {
				mr = r;
				mx = i;
			}
		}

		printf("Between %d and %d, %d generates the longest sequence "
		       "of %d values.\n", a, b, mx, mr);
	}

	return 0;
}
