/*
ID: mjf28791
PROG: friday
LANG: C
*/
#include <stdio.h>

int main()
{
	int a[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, c[8];
	int ymax, i, d, y, m;

	freopen("friday.in", "r", stdin);
	freopen("friday.out", "w", stdout);

	scanf("%d", &ymax);
	ymax += 1900;

	y = 1900;
	m = 1;
	d = 0;

	for (i = 0; i < 8; i++)
		c[i] = 0;

	while (y < ymax) {
		c[(13 + d) % 7]++;

		d += a[m];

		if (m == 12) {
			y++;
			m = 1;
		} else if (m == 2) {
			if ((y % 4) == 0 && ((y % 100) != 0 || (y % 400) == 0))
				d++;
			m = 3;
		} else {
			m++;
		}
	}

	for (i = 0; i < 7; i++)
		printf((i < 6) ? "%d " : "%d\n", c[(i + 6) % 7]);

	return 0;
}
