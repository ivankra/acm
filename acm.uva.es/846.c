#include <stdio.h>

/* floor[sqrt(a)] */
static unsigned long int_sqrt(unsigned long a)
{
	register unsigned long x = a, y;

	for (;;) {
		y = (x + (a / x)) >> 1;

		if (y >= x)
			return x;
		else
			x = y;
	}
}

int main(void)
{
	static unsigned n, x, y;
	register unsigned i, t;

	scanf("%u\n", &n);
	while (n-- > 0) {
		if (scanf("%u %u", &x, &y) != 2) break;

		i = (x < y) ? (y - x) : (x - y);

		if (i < 4) {
			printf("%u\n", i);
		} else {
			t = int_sqrt(i - 1);
			printf("%u\n", t + t + ((i > (t*t + t)) ? 1 : 0));
		}
	}

	return 0;
}
