#include <stdio.h>

int main()
{
	static int tab[16384], drink[16384];
	int k, n, m, t;

	while (scanf("%d %d %d", &n, &m, &t) == 3) {
		for (k = 0; k <= t; k++) {
			tab[k] = 0;
			drink[k] = k;

			if (k >= n) {
				tab[k] = 1 + tab[k - n];
				drink[k] = drink[k - n];
			}

			if (k >= m) {
				if (drink[k - m] < drink[k]) {
					tab[k] = 1 + tab[k - m];
					drink[k] = drink[k - m];
				} else if (drink[k - m] == drink[k]) {
					if (tab[k] < (1 + tab[k - m]))
						tab[k] = 1 + tab[k - m];
				}
			}
		}

		printf(drink[t] ? "%d %d\n" : "%d\n", tab[t], drink[t]);
	}

	return 0;
}
