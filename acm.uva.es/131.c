#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SUIT(x) ((x) >> 8)
#define FACE(x) ((x) & 0xFF)

int get()
{
	int c, v;
	static char s[] = "A23456789TJQK";

	for (;;) {
		if ((c = getchar()) == EOF)
			return -1;

		for (v = 0, c = toupper(c); s[v]; v++)
			if (s[v] == c) break;

		if (s[v] == 0)
			continue;

		switch (toupper(getchar())) {
			case 'S': return (v | 0x000);
			case 'C': return (v | 0x100);
			case 'H': return (v | 0x200);
			default:  return (v | 0x300);
		}
	}
}

void print_cards(int c[], int n)
{
	static char f[] = "A23456789TJQK", s[] = "SCHD";
	int i;

	for (i = 0; i < n; i++)
		printf(i ? " %c%c" : "%c%c", f[FACE(c[i])], s[SUIT(c[i])]);
}

int rank(int h[])
{
	int i, j;
	int faces[13], suits[4];
	int faces_p[6], suits_p[6], straight;

	for (i = 0; i < 13; i++) faces[i] = 0;
	for (i = 0; i < 4; i++) suits[i] = 0;
	for (i = 0; i < 6; i++) faces_p[i] = suits_p[i] = 0;

	for (i = 0; i < 5; i++) {
		faces[FACE(h[i])]++;
		suits[SUIT(h[i])]++;
	}

	for (i = 0; i < 13; i++)
		faces_p[faces[i]]++;

	for (i = 0; i < 4; i++)
		suits_p[suits[i]]++;

	for (i = 1; i < 13 && faces[i] == 0; i++);
	for (j = 0; i < 13 && faces[i] == 1; i++, j++);
	if (faces[0] == 1 && (faces[1] == 1 || faces[12] == 1) && j == 4) j++;
	straight = (j == 5) ? 1 : 0;

	if (straight && suits_p[5]) return 0;		/* straight-flush */
	if (faces_p[4]) return 1;			/* four of a kind */
	if (faces_p[3] && faces_p[2]) return 2;		/* full house */
	if (suits_p[5]) return 3;			/* flush */
	if (straight) return 4;				/* straight */
	if (faces_p[3]) return 5;			/* three of a kind */
	if (faces_p[2] == 2) return 6;			/* two pairs */
	if (faces_p[2] == 1) return 7;			/* one pair */
	return 8;					/* high card */
}

int main()
{
	char *ranks[] = {
		"straight-flush",
		"four-of-a-kind",
		"full-house",
		"flush",
		"straight",
		"three-of-a-kind",
		"two-pairs",
		"one-pair",
		"highest-card"
	};
	int c[15], i, j, k, r, m;

	for (;;) {
		for (i = 0; i < 10; i++)
			if ((c[i] = get()) == -1) break;
		if (i < 10) break;

		printf("Hand: "); print_cards(c, 5);
		printf(" Deck: "); print_cards(c+5, 5);

		for (i = 0, m = 0; i < 32; i++) {
			for (j = 0, k = 0; j < 5; j++)
				if (((i >> j) & 1) == 0) {
					c[10 + j] = c[j];
				} else {
					c[10 + j] = c[5 + k];
					k++;
				}

			r = rank(c + 10);
			if (i == 0 || r < m) {
				m = r;
			}
		}

		printf(" Best hand: %s\n", ranks[m]);
	}

	return 0;
}
