#include <stdio.h>
#include <memory.h>

static int tab[1000001], q;

int main()
{
	register int i, j, k;

	memset(tab, 0, sizeof(tab));
	for (i = 2; i <= 1000000; i++) {
		if (tab[i] != 0) continue;

		for (k = i;;) {
			for (j = k; j <= 1000000; j += k)
				tab[j]++;

			if (i > 1000) break;
			if ((k *= i) >= 1000000) break;
		}
	}

	for (i = 2, k = 0; i <= 1000000; i++) {
		k += tab[i];
		tab[i] = k;
	}

	while (scanf("%d", &q) == 1)
		printf("%d\n", tab[q]);

	return 0;
}
