#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isvowel[256], used[4][4], alpha[4], word[4], len;
unsigned char *bitmap;
char square[16];

void find(int y, int x)
{
	int i, j;

	used[y][x] = 1;
	alpha[len] = square[4 * y + x];
	word[len] = ((len == 0) ? 0 : (word[len - 1] * 26)) + alpha[len] - 'A';
	len++;

	if (len >= 4) {
		for (i = 0, j = 0; i < 4; i++)
			if (isvowel[alpha[i]]) j++;

		if (j == 2) {
			i = word[3];
			bitmap[i >> 3] |= 1 << (i & 7);
		}

		len--;
		used[y][x] = 0;

		return;
	}

	for (i = y - 1; i <= (y + 1); i++) {
		if (i < 0) continue;
		if (i > 3) continue;

		for (j = x - 1; j <= (x + 1); j++) {
			if (j < 0) continue;
			if (j > 3) continue;

			if (used[i][j]) continue;

			find(i, j);
		}
	}

	len--;
	used[y][x] = 0;
}

void process(char *s, unsigned char *b)
{
	int i, j;

	memset(b, 0, 65536);
	memcpy(square, s, 16);
	bitmap = b;

	memset(used, 0, sizeof(used));
	memset(word, 0, sizeof(word));
	len = 0;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			find(i, j);
}

int main()
{
	static char a[16], b[16];
	static unsigned char bit1[65536], bit2[65536];
	int i, j, c, t;

	memset(isvowel, 0, sizeof(isvowel));
	for (i = 0; (c = "AEIOUY"[i]) != '\0'; i++)
		isvowel[c] = 1;

	for (t = 0;; t++) {
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4 && (c = getchar()) != EOF && c != '#';)
				if (isalpha(c)) a[4 * i + j++] = toupper(c);
			if (j < 4) break;

			for (j = 0; j < 4 && (c = getchar()) != EOF;)
				if (isalpha(c)) b[4 * i + j++] = toupper(c);
		}
		if (i < 4) break;

		process(a, bit1);
		process(b, bit2);

		if (t != 0) printf("\n");

		for (i = 0, j = 0; i < 456976; i++) {
			if ((((bit1[i >> 3] & bit2[i >> 3]) >> (i & 7)) & 1) == 0)
				continue;

			printf("%c%c%c%c\n",
				(i / 17576) + 'A', ((i / 676) % 26) + 'A',
				((i / 26) % 26) + 'A', (i % 26) + 'A');
			j++;
		}

		if (j == 0)
			printf("There are no common words for this pair of boggle boards.\n");
	}

	return 0;
}
