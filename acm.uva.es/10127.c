#include <stdio.h>

int main()
{
	static int tab[10001], n;
	register int i, t;

	for (i = 0; i <= 10000; i++)
		tab[i] = 0;

	while (scanf("%d", &n) == 1) {
		if (tab[n] == 0) {
			for (i = 1, t = 1; t != 0; i++)
				t = (10 * t + 1) % n;
			tab[n] = i;
		}

		printf("%d\n", tab[n]);
	}

	return 0;
}
