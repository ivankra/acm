/*
ID: mjf28791
PROG: preface
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
	static struct {
		int x;
		char s[4];
	} tab[] = {
		{ 1,	"I" },	{ 4,	"IV" },	{ 5,	"V" },	{ 9,	"IX" },
		{ 10,	"X" },	{ 40,	"XL" },	{ 50,	"L" },	{ 90,	"XC" },
		{ 100,	"C" },	{ 400,	"CD" },	{ 500,	"D" },	{ 900,	"CM" },
		{ 1000,	"M" },	{ 4000,	"" }
	};
	static int c[4096][8], map[256];
	int i, j, k, x, v;

	memset(c, 0, sizeof(c));
	for (i = 0; (k = "IVXLCDM"[i]) != '\0'; i++)
		map[k] = i;

	for (k = 0; tab[k].x <= 1000; k++) {
		for (x = v = tab[k].x; x < tab[k + 1].x; x++) {
			for (i = 0; i < 8; i++)
				c[x][i] = c[x - v][i];

			for (i = 0; tab[k].s[i]; i++)
				c[x][map[tab[k].s[i]]]++;
		}
	}

	for (x = 1; x < 4000; x++)
		for (i = 0; i < 8; i++) c[x][i] += c[x - 1][i];

	freopen("preface.in", "r", stdin);
	freopen("preface.out", "w", stdout);

	for (scanf("%d", &x), i = 0; i < 8; i++)
		if (c[x][i]) printf("%c %d\n", "IVXLCDM"[i], c[x][i]);
}

