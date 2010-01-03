#include <stdio.h>
#include <stdlib.h>

void roman(int r[], int n)
{
	static struct {
		char *s;
		int a;
	} tab[] = {
		{ "i", 1 },	{ "iv", 4 },	{ "v", 5 },	{ "ix",	9 },
		{ "x", 10 },	{ "xl", 40 },	{ "l", 50 },	{ "xc", 90 },
		{ "c", 100 },	{ NULL, 0 }
	};
	static int map[256];
	char *p;
	int i;

	if (n <= 0)
		return;

	for (i = 0; tab[i+1].s; i++)
		if (tab[i].a <= n && n < tab[i+1].a) break;

	map['i'] = 0;
	map['v'] = 1;
	map['x'] = 2;
	map['l'] = 3;
	map['c'] = 4;

	for (p = tab[i].s; *p; p++)
		r[map[*p]]++;

	roman(r, n - tab[i].a);
}

int main()
{
	static int r[128][8];
	int i, j, n;

	memset(r, 0, sizeof(r));

	for (i = 1; i <= 100; i++) {
		for (j = 0; j < 5; j++) r[i][j] = r[i-1][j];
		roman(r[i], i);
	}

	while (scanf("%d", &n) == 1 && n > 0) {
		printf("%d: %d i, %d v, %d x, %d l, %d c\n",
			n, r[n][0], r[n][1], r[n][2], r[n][3], r[n][4]);
	}

	return 0;
}
