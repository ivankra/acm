/*
ID: mjf28791
PROG: dualpal
LANG: C
*/
#include <stdio.h>

int ispal(int n, int b)
{
	int r, t;

	for (t = n, r = 0; t > 0; t /= b)
		r = r * b + t % b;

	return (r == n);
}

int isdpal(int n)
{
	int b, k;

	for (b = 2, k = 0; b <= 10 && k < 2; b++)
		if (ispal(n, b)) k++;

	return (k >= 2);
}

int main()
{
	int n, s;

	freopen("dualpal.in", "r", stdin);
	freopen("dualpal.out", "w", stdout);

	scanf("%d %d", &n, &s);
	for (s++; n > 0; s++)
		if (isdpal(s)) printf("%d\n", s), n--;

	return 0;
}
