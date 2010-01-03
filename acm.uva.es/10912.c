#include <stdio.h>
#include <string.h>

char got[27][27][512];
int tab[27][27][512];

int f(int a, int l, int s)
{
	int i, r;

	if (l == 0) return (s == 0) ? 1 : 0;
	if (s < 0 || a > 26 || l > 26 || s > 360) return 0;

	if (got[a][l][s]) return tab[a][l][s];
	for (r = 0, i = a; i <= 26; i++)
		r += f(i + 1, l - 1, s - i);
	got[a][l][s] = 1;
	return (tab[a][l][s] = r);
}

int main()
{
	int L, S, t;

	memset(got, 0, sizeof(got));
	for (t = 1; scanf("%d %d", &L, &S) == 2 && L > 0; t++)
		printf("Case %d: %d\n", t, f(1, L, S));

	return 0;
}
