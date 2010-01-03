/*
ID: infnty1
PROB: friday
LANG: C++
*/
#include <stdio.h>

int main()
{
	int d[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	int w, y, m, n, c[8];

	freopen("friday.in", "r", stdin);
	freopen("friday.out", "w", stdout);

	for (n = 0; n < 8; n++) c[n] = 0;

	scanf("%d", &n);
	for (w = 14, y = 1900, m = 1, n *= 12; n-- > 0;) {
		c[w%7]++;
		d[2] = ((y%400)==0 || ((y%4)==0 && (y%100)!=0)) ? 29 : 28;
		w += d[m];
		if (++m > 12) { y++; m = 1; }
	}

	for (n = 0; n < 7; n++)
		printf(n<6 ? "%d " : "%d\n", c[n]);

	return 0;
}
