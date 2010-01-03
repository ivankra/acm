#include <stdio.h>

int main()
{
	static unsigned r, b, e, m;

	while (scanf("%u %u %u", &b, &e, &m) == 3) {
		for (b %= m, r = 1; e > 0; e >>= 1) {
			if (e & 1)
				r = (r * b) % m;
			if (e > 1)
				b = (b * b) % m;
		}

		printf("%u\n", r);
	}

	return 0;
}
