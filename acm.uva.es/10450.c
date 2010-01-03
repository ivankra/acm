#include <stdio.h>

int main()
{
	static long long tab[64];
	int i, n, t, a;

	tab[0] = 1;
	tab[1] = 2;
	for (i = 2; i < 52; i++)
		tab[i] = tab[i - 1] + tab[i - 2];

	for (scanf("%d", &n), t = 1; t <= n && scanf("%d", &a) == 1; t++)
		printf("Scenario #%d:\n%lld\n\n", t, tab[a]);

	return 0;
}
