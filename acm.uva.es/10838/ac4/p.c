#include <stdio.h>
#include <string.h>

#define GET(a,i) (((a) >> (i)) & 1)
#define BIT(i) (1 << (i))

static unsigned enc16[65536], enc8[256], enc8_m2[256];
static signed char table[39203 * 70 * 2 + 1024];

static void mktab()
{
	static int a[16];
	int i, j, k, m;

	enc16[0] = 0;
	m = 1;

	for (a[0] = -1, k = 0; k >= 0;) {
		if (++a[k] >= 16) {
			k--;
			continue;
		}

		for (i = 0, j = 0; i <= k; i++)
			j |= BIT(a[i]);
		enc16[j] = m++;

		if (k < 7) {
			a[k + 1] = a[k];
			k++;
		}
	}

	m = 0;

	for (a[0] = -1, k = 0; k >= 0;) {
		if (++a[k] >= 8) {
			k--;
			continue;
		}

		for (i = 0, j = 0; i <= k; i++)
			j |= BIT(a[i]);
		enc8[j] = m;

		if (k < 3) {
			a[k + 1] = a[k];
			k++;
		} else {
			m++;
		}
	}

	for (k = 0; k < 256; k++) {
		for (i = 0, j = 0; i < 8; i++)
			j += (k >> i) & 1;

		if (j > 4)
			continue;

		for (i = k; j < 4; j++)
			i |= (1 << (j + 4));

		enc8[k] = enc8[i];
	}

	for (k = 0; k < 256; k++)
		enc8_m2[k] = enc8[k] << 1;
}

static unsigned encode(unsigned w, unsigned b, unsigned m)
{
	register int i, r, s;

	s = (b | w);

	for (i = 0, r = 0; i < 16; s >>= 1, i++)
		if (s & 1) r = (r << 1) | ((w >> i) & 1);

	return enc16[w | b] * 140 + enc8_m2[r] + m;
}

static int play(unsigned w, unsigned b, unsigned m)
{
	unsigned cfg;
	int win, lose, k, s, t;

	cfg = encode(w, b, m);

	if (table[cfg] != 0)
		return table[cfg];

	s = w | b;

	if (m == 0) {
		if ((b & 0x000F) || (w == 0))
			return (table[cfg] = -1);

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
		if ((w & 0xF000) || b == 0)
			return (table[cfg] = 1);

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
	static int w, b, i, c, t;

	mktab();
	/*memset(table, 0, sizeof(table));*/

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
