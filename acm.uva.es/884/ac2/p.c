#include <stdio.h>

static int tab[1000001], q, sum;

int main()
{
	register int i, j, k;

	for (i = 0; i < 1000000; i++)
		tab[i] = 0;

	for (k = 2; k <= 1000000; k <<= 1) {
		for (j = k; j <= 1000000; j += k)
			tab[j]++;
	}

	for (i = 3; i < 1001; i += 2) {
		if (tab[i] != 0) continue;

		for (k = i; k <= 1000000; k *= i) {
			for (j = k; j <= 1000000; j += k)
				tab[j]++;
		}
	}

	for (i = 1001; i <= 1000000; i += 2) {
		if (tab[i] != 0) continue;

		for (j = i; j <= 1000000; j += i)
			tab[j]++;
	}

	for (i = 2, k = 0; i <= 1000000; i++) {
		k += tab[i];
		tab[i] = k;
	}

	while (scanf("%d", &q) == 1)
		printf("%d\n", tab[q]);

	return 0;
}
