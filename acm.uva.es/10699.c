#include <stdio.h>

#define MAXN 1000010

int main()
{
	static int tab[MAXN], n;
	register int i, j;

	for (i = 0; i < MAXN; i++)
		tab[i] = 0;

	for (i = 2; i < MAXN; i++) {
		if (tab[i] != 0)
			continue;

		tab[i] = 1;

		for (j = i + i; j < MAXN; j += i)
			tab[j]++;
	}

	while (scanf("%d", &n) == 1 && n > 0)
		printf("%d : %d\n", n, tab[n]);

	return 0;
}
