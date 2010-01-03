/*
ID: mjf28791
PROG: ride
LANG: C
*/
#include <stdio.h>

int main()
{
	char s[256], t[256];
	int x, y, i;

	freopen("ride.in", "r", stdin);
	freopen("ride.out", "w", stdout);

	scanf(" %[A-Z] %[A-Z]", s, t);

	for (x = 1, i = 0; s[i]; i++)
		x *= s[i] - 'A' + 1;

	for (y = 1, i = 0; t[i]; i++)
		y *= t[i] - 'A' + 1;

	printf(((x % 47) == (y % 47)) ? "GO\n" : "STAY\n");

	return 0;
}
