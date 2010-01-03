#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct { int r, s; } card;

int eval(card c[])
{
	int i, j, fl, st, ki, no[16];

	for (i = 0; i < 16; i++)
		no[i] = 0;

	for (i = 0; i < 5; i++)
		no[c[i].r]++;

	for (i = 1; i < 5 && c[i].s == c[0].s; i++);
	fl = (i == 5);

	st = 0;
	for (i = 0; st == 0 && i < 13; i++) {
		for (j = 0; j < 5; j++)
			if (no[(i + j) % 13] != 1) break;
		if (j == 5) st = 1;
	}

	for (ki = 0, i = 0; i < 13; i++)
		if (no[i] > ki) ki = no[i];

	if (st && fl) return 9;
	if (ki == 4) return 8;
	if (ki == 3) for (i = 0; i < 13; i++) if (no[i] == 2) return 7;
	if (fl) return 6;
	if (st) return 5;
	if (ki == 3) return 4;

	for (i = 0, j = 0; i < 13; i++)
		if (no[i] == 2) j++;
	if (j == 2) return 3;

	if (ki == 2) return 2;
	return 1;
}

card get()
{
	char s[] = "A23456789XJQK";
	card a;
	int c;

	while ((c = getchar()) != EOF && !isalnum(c));
	a.r = strchr(s, toupper(c)) - s;

	while ((c = getchar()) != EOF && !isalnum(c));
	a.s = toupper(c);

	return a;
}

int main()
{
	card a[8][8], b[8][8];
	int i, j, t, c[16];

	for (scanf("%d", &t); t-- > 0;) {
		for (i = 0; i < 5; i++)
			for (j = 0; j < 5; j++)
				a[i][j] = b[j][i] = get();

		for (i = 1; i <= 9; i++)
			c[i] = 0;

		for (i = 0; i < 5; i++) {
			c[eval(&a[i][0])]++;
			c[eval(&b[i][0])]++;
		}

		for (i = 1; i <= 9; i++)
			printf((i < 9) ? "%d, " : "%d\n", c[i]);
		if (t) printf("\n");
	}

	return 0;
}
