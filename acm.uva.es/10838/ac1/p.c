#include <stdio.h>
#include <string.h>

#define GET(a,i) (((a) >> (i)) & 1)
#define BIT(i) (1 << (i))

static int enc84[8][8][8][8];
static short table[9175040+1024];

static void mktab()
{
	int a, b, c, d, k;

	for (k = 0, a = 0; a < 8; a++)
		for (b = a + 1; b < 8; b++)
			for (c = b + 1; c < 8; c++)
				for (d = c + 1; d < 8; d++)
					enc84[a][b][c][d] = (k++ << 1);
}

static int encode(int w, int b, int m)
{
	static int a[16];
	int i, j, k;

	a[0] = 4;
	a[1] = 5;
	a[2] = 6;
	a[3] = 7;

	for (i = 0, j = 0, k = 0; i < 16; i++) {
		if ((((w | b) >> i) & 1) == 0)
			continue;

		if (((w >> i) & 1) != 0)
			a[k++] = j;

		j++;
	}

	return ((w | b) * 140) + enc84[a[0]][a[1]][a[2]][a[3]] + m;
}

static int play(int w, int b, int m)
{
	int win, lose, cfg, k, s, t;

	cfg = encode(w, b, m);

	if (table[cfg] != 0)
		return table[cfg];

	s = w | b;

	if (m == 0) {
		if (b & 0x000F) return (table[cfg] = -1);
		if (w == 0) return (table[cfg] = -1);

		for (win = lose = 0, k = 0; k < 12; k++) {
			if (GET(w, k) == 0)
				continue;

			if (GET(s, k + 4) == 0) {
				t = play(w ^ BIT(k) ^ BIT(k+4), b, 1);
				if (t > 0 && (win == 0 || t < win))
					win = t;
				else if (t < 0 && t < lose)
					lose = t;
			}

			if ((k & 3) != 3 && GET(b, k + 5)) {
				t = play(w ^ BIT(k) ^ BIT(k+5), b ^ BIT(k+5), 1);
				if (t > 0 && (win == 0 || t < win))
					win = t;
				else if (t < 0 && t < lose)
					lose = t;
			}

			if ((k & 3) != 0 && GET(b, k + 3)) {
				t = play(w ^ BIT(k) ^ BIT(k+3), b ^ BIT(k+3), 1);
				if (t > 0 && (win == 0 || t < win))
					win = t;
				else if (t < lose)
					lose = t;
			}
		}

		if (win != 0)
			return table[cfg] = win + 1;
		else
			return table[cfg] = lose - 1;
	} else {
		if (w & 0xF000) return (table[cfg] = 1);
		if (b == 0) return (table[cfg] = 1);

		for (win = lose = 0, k = 4; k < 16; k++) {
			if (GET(b, k) == 0)
				continue;

			if (GET(s, k - 4) == 0) {
				t = play(w, b ^ BIT(k) ^ BIT(k-4), 0);
				if (t < 0 && (win == 0 || win < t))
					win = t;
				else if (lose < t)
					lose = t;
			}

			if ((k & 3) != 3 && GET(w, k - 3)) {
				t = play(w ^ BIT(k-3), b ^ BIT(k) ^ BIT(k-3), 0);
				if (t < 0 && (win == 0 || win < t))
					win = t;
				else if (lose < t)
					lose = t;
			}

			if ((k & 3) != 0 && GET(w, k - 5)) {
				t = play(w ^ BIT(k-5), b ^ BIT(k) ^ BIT(k-5), 0);
				if (t < 0 && (win == 0 || win < t))
					win = t;
				else if (lose < t)
					lose = t;
			}
		}

		if (win != 0)
			return table[cfg] = win - 1;
		else
			return table[cfg] = lose + 1;
	}
}

int main()
{
	int w, b, i, c, t;

	mktab();

	memset(table, 0, sizeof(table));

	for (scanf("%d", &t) == 1; t-- > 0;) {
		for (w = b = 0, i = 15; i >= 0 && (c = getchar()) != EOF;) {
			if (c == '.')
				i--;
			else if (c == 'P')
				w |= (1 << i--);
			else if (c == 'p')
				b |= (1 << i--);
		}

		i = play(w, b, 0);

		if (i < 0)
			printf("black (%d)\n", -i - 1);
		else
			printf("white (%d)\n", i - 1);
	}

	return 0;
}
