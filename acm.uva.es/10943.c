#include <stdio.h>
#include <string.h>

int tab[128][128];

void make()
{
	int i, n, k;

	memset(tab, 0, sizeof(tab));
	tab[0][0] = 1;

	for (k = 1; k <= 127; k++)
		for (n = 0; n <= 127; n++)
			for (i = 0; i <= n; i++)
				tab[n][k] = (tab[n][k] + tab[n-i][k-1]) % 1000000;
}

int main()
{
	int n, k;

	make();
	while (scanf("%d %d", &n, &k) == 2 && n > 0 && k > 0)
		printf("%d\n", tab[n][k] % 1000000);

	return 0;
}
