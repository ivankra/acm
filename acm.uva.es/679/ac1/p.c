#include <stdio.h>

int main()
{
	static int t, d, s;
	register int p;

	for (scanf("%d", &t); t-- > 0 && scanf("%d%d", &d, &s) == 2;) {
		for (p = 1, s--; d-- > 1; s >>= 1)
			if (s & 1)
				p = (p << 1) + 1;
			else
				p <<= 1;

		printf("%d\n", p);
	}

	return 0;
}
