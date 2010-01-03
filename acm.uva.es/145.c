#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct {
	int a, b, c;
} tab[] = {
	{ 0, 8 * 60, 2 },
	{ 8 * 60, 18 * 60, 0 },
	{ 18 * 60, 22 * 60, 1 },
	{ 22 * 60, (24 + 8) * 60, 2 },
	{ (24 + 8) * 60, (24 + 18) * 60, 0 },
	{ (24 + 18) * 60, (24 + 22) * 60, 1 },
	{ (24 + 22) * 60, (48 + 8) * 60, 2 },
};

int rate[3][5] = {
	{ 10, 25, 53, 87, 144 },
	{ 6, 15, 33, 47, 80 },
	{ 2, 5, 13, 17, 30 }
};

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int main()
{
	char s[256], phone[256];
	int c[3], d, h1, m1, h2, m2, t1, t2;
	int i, k;

	while (scanf(" %s %s %d %d %d %d", s, phone, &h1, &m1, &h2, &m2) > 0) {
		if (strchr(s, '#') != NULL)
			break;

		d = toupper(s[0]) - 'A';
		if (d < 0) d = 0;
		if (d > 4) d = 4;

		t1 = h1 * 60 + m1;
		t2 = h2 * 60 + m2;

		if (t2 <= t1)
			t2 += 24 * 60;

		memset(c, 0, sizeof(c));

		for (i = 0; i < (sizeof(tab) / sizeof(tab[0])); i++)
			c[tab[i].c] += max(0, min(tab[i].b, t2) - max(tab[i].a, t1));

		for (k = 0, i = 0; i < 3; i++)
			k += c[i] * rate[i][d];

		printf("%10s%6d%6d%6d  %c%5d.%.2d\n",
			phone, c[0], c[1], c[2], d + 'A', k / 100, k % 100);
	}

	return 0;
}
