/*
ID: infnty1
PROB: palsquare
LANG: C++
*/
#include <stdio.h>

int rev(int n, int b)
{
	int r;
	for (r = 0; n > 0; n /= b) r = r * b + (n % b);
	return r;
}

char *fmt(int n, int b)
{
	static char z[2][256], dig[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static int Z = 0;
	char *p = z[Z = (Z + 1) & 1]+250;
	for (*p=0; n > 0; n /= b) *--p = dig[n % b];
	return p;
}

int main()
{
	freopen("palsquare.in", "r", stdin);
	freopen("palsquare.out", "w", stdout);

	int b;
	scanf("%d", &b);

	for (int i = 1; i <= 300; i++)
		if (i*i == rev(i*i, b)) printf("%s %s\n", fmt(i,b), fmt(i*i,b));

	return 0;
}
