#include <stdio.h>
#include <string.h>
#include <ctype.h>

int ranks[256];
char card[52][4];

int get()
{
	int s, c;

	while ((s = getchar()) != EOF && !isalpha(s));
	if (s == EOF) return EOF;

	while ((c = getchar()) != EOF && !isalnum(c));
	if (c == EOF) return EOF;

	s = toupper(s);
	c = ranks[c];
	if (s == 'C')
		return c;
	else if (s == 'D')
		return 13 + c;
	else if (s == 'S')
		return 26 + c;
	else
		return 39 + c;
}

void sort(int a[], int n)
{
	int i, j, t;

	for (i = 1; i < n; i++) {
		for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
			a[j + 1] = a[j];
		a[j + 1] = t;
	}
}

void print(char s, int a[])
{
	int i;

	printf("%c:", s);
	for (i = 0; i < 13; i++)
		printf(" %s", card[a[i]]);
	printf("\n");
}

int main()
{
	static int a[64], p[4][16], k[4];
	int i, j, c;

	for (i = 0; (j = "23456789TJQKA"[i]) != '\0'; i++)
		ranks[j] = ranks[tolower(j)] = i;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 13; j++)
			sprintf(card[13 * i + j], "%c%c",
				"CDSH"[i], "23456789TJQKA"[j]);
	}

	while ((c = getchar()) != EOF && c != '#') {
		if (strchr("NSWE", c = toupper(c)) == NULL)
			continue;

		for (i = 0; i < 52; i++)
			a[i] = get();

		if (c == 'S')
			i = 1;
		else if (c == 'W')
			i = 2;
		else if (c == 'N')
			i = 3;
		else
			i = 0;

		k[0] = k[1] = k[2] = k[3] = 0;

		for (j = 0; j < 52; j++, i = (i + 1) & 3)
			p[i][k[i]++] = a[j];

		for (i = 0; i < 4; i++) {
			sort(p[i], 13);
			print("SWNE"[i], p[i]);
		}
	}

	return 0;
}
