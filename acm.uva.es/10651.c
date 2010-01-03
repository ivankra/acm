#include <stdio.h>

#define INF 0x3FFFFFFF
#define BIT(x,k) (((x) >> (k)) & 1)

int tab[4096];

int min(int x, int y) { return (x < y) ? x : y; }

int f(int a)
{
	int i;

	if (tab[a] >= 0) return tab[a];

	for (tab[a] = 0, i = 0; i < 12; i++)
		tab[a] += (a >> i) & 1;

	for (i = 1; i < 11; i++)
		if (BIT(a,i) == 1 && (BIT(a,i-1) ^ BIT(a,i+1)) == 1)
			tab[a] = min(tab[a], f(a ^ (7 << (i-1))));

	return tab[a];
}

int main()
{
	int i, j, c, t;

	for (i = 0; i < 4096; i++) tab[i] = -1;
	for (i = 0; i < 4096; i++) f(i);

	for (scanf("%d", &t); t-- > 0;) {
		for (j = 0, i = 0; i < 12 && (c = getchar()) != EOF;)
			if (c == 'o')
				i++, j = (j << 1) | 1;
			else if (c == '-')
				i++, j <<= 1;
		printf("%d\n", tab[j]);
	}

	return 0;
}
