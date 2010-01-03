#include <stdio.h>

char s[1024];
int q[16], tab[15625], got[15625];

int f(int s, int r)
{
	int k;

	if (got[r] == 42) return tab[r];
	got[r] = 42;

	if (s > 31) return tab[r] = 0;

	for (k = 0; k < 6; k++)
		if (((r / q[k]) % 5) != 4 && s+k+1 <= 31 && f(s+k+1, r + q[k]) == 0)
			return tab[r] = 1;
	return tab[r] = 0;
}

int solve()
{
	int i, j, k, z, w;

	for (q[0] = 1, i = 1; i < 16; i++)
		q[i] = q[i-1] * 5;

	for (z = w = k = 0, i = 0; s[i]; i++)
		if ('1' <= s[i] && s[i] <= '6') {
			k ^= 1;
			w += s[i] - '0';
			z += q[s[i] - '1'];
		}

	return (f(w,z) ? k : (k ^ 1)) + 'A';
}

int main()
{
	while (gets(s))
		printf("%s %c\n", s, solve());
	return 0;
}
