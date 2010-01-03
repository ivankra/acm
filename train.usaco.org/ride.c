/*
ID: infnty1
PROB: ride
LANG: C
*/
#include <stdio.h>

int f(char *s)
{
	int r;
	for (r = 1; *s; s++)
		r *= *s - 'A' + 1;
	return r % 47;
}

int main()
{
	char s1[10], s2[10];
	int x, y, i;

	freopen("ride.in", "r", stdin);
	freopen("ride.out", "w", stdout);
	scanf(" %s %s", s1, s2);
	printf((f(s1) == f(s2)) ? "GO\n" : "STAY\n");

	return 0;
}
