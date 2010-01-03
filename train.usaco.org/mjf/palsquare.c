/*
ID: mjf28791
PROG: palsquare
LANG: C
*/
#include <stdio.h>

int ispal(int n, int b)
{
	int r, t;

	for (r = 0, t = n; t > 0; t /= b)
		r = r * b + (t % b);

	return (r == n);
}

char *fmt(int n, int b)
{
	static char s[2][1024], t[1024];
	static int z = 0;
	int i, k;

	for (k = 0; n > 0; n /= b)
		t[k++] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[n % b];

	z = (z + 1) & 1;

	for (i = 0; k-- > 0;)
		s[z][i++] = t[k];
	s[z][i] = '\0';

	return s[z];
}

int main()
{
	int n, b;

	freopen("palsquare.in", "r", stdin);
	freopen("palsquare.out", "w", stdout);

	scanf("%d", &b);
	for (n = 1; n <= 300; n++)
		if (ispal(n * n, b))
			printf("%s %s\n", fmt(n, b), fmt(n * n, b));

	return 0;
}
