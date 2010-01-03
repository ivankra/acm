#include <stdio.h>



int main()
{
	static int tab[128][128], b, n;
	register int i, k, s;

	while (scanf("%d %d", &b, &n) == 2 && b > 0) {
		for (tab[1][0] = 0, i = 1; i < b; i++)
			tab[1][i] = 1;

		for (k = 1, s = 0; k <= n;) {
			for (i = 0, s = 0; i < b; i++)
				s += tab[k][i];

			if (k++ == n)
				break;

			for (i = 0; i < b; i++)
				tab[k][i] = s;
			tab[k][3] -= tab[k - 1][1];
		}

		printf("%d\n", s);
	}

	return 0;
}
