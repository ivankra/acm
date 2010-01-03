#include <stdio.h>

int main()
{
	static unsigned n, l, u;
	register unsigned m, t;
	register int i;

	while (scanf("%u %u %u", &n, &l, &u) == 3) {
		for (m = l, i = 31; i >= 0; i--) {
			t = (1 << i);

			if ((m & t) == 0 && (n & t) == 0 &&
			    ((m | t) & ~((1 << i) - 1)) <= u) {
				m |= t;
				m &= ~((1 << i) - 1);
			}
		}

		printf("%u\n", m);
	}

	return 0;
}
