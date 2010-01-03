#include <stdio.h>
#include <string.h>

char got[71][71][71];
unsigned tab[71][71][71];

unsigned f(unsigned n, unsigned s, unsigned b)
{
	unsigned k, r;

	if (got[n][s][b]) return tab[n][s][b];

	got[n][s][b] = 1;
	if (n == 1)
		return tab[n][s][b] = ((s < b) ? 0 : 1);

	for (r = 0, k = b; k <= s; k++)
		r += f(n - 1, s - k, b);

	tab[n][s][b] = r;
	return r;
}

int main()
{
	int n, s, b, t;

	memset(got, 0, sizeof(got));
	for (scanf("%d", &t); t-- > 0 && scanf("%d %d %d", &n, &s, &b) == 3;)
		printf("%u\n", f(n, s, b));

	return 0;
}
