#include <stdio.h>

int main()
{
	unsigned long n, tab[14];
	register int i;

	for (n = 1, i = 0; i < 14; i++) {
		n *= (i & 1) ? 2 : 9;
		tab[i] = n;
	}

	while (scanf("%u", &n) > 0) {
		for (i = 0; i < 14; i++)
			if (n <= tab[i]) break;

		printf((i & 1) ? "Ollie wins.\n" : "Stan wins.\n");
	}

	return 0;
}
