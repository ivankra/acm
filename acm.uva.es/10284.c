#include <stdio.h>
#include <string.h>

static int piece[64], color[64], attacked[64];

#define CELL(row,col) (((row) << 3) + (col))
#define ROW(cell) ((cell) >> 3)
#define COL(cell) ((cell) & 7)

#define PIECE(r,c) piece[CELL(r,c)]
#define COLOR(r,c) color[CELL(r,c)]
#define ATTACKED(r,c) attacked[CELL(r,c)]

#define VALID(r,c) (((r)>=0)&&((r)<8)&&((c)>=0)&&((c)<8))
#define FREE(r,c) (VALID(r,c) && PIECE(r,c)==0)
#define MARK(r,c) { if (VALID(r,c)) ATTACKED(r,c) = 1; }

static void parse(char *s)
{
	int i;

	for (i = 0; i < 64; i++)
		piece[i] = 0, color[i] = 0, attacked[i] = 0;

	for (i = 0; *s; s++) {
		if (*s >= '1' && *s <= '8') {
			i += *s - '0';
			continue;
		}

		if (strchr("PNBRQK", *s) != NULL) {
			piece[i] = *s;
			color[i] = 'W';
			i++;
		} else if (strchr("pnbrqk", *s) != NULL) {
			piece[i] = *s - 'a' + 'A';
			color[i] = 'B';
			i++;
		}
	}
}

static void pawns()
{
	register int r, c;

	for (r = 0; r < 7; r++) {
		for (c = 0; c < 8; c++) {
			if (PIECE(r,c) != 'P') continue;
			if (COLOR(r,c) == 'B') {
				MARK(r + 1, c - 1);
				MARK(r + 1, c + 1);
			} else {
				MARK(r - 1, c - 1);
				MARK(r - 1, c + 1);
			}
		}
	}
}

static void knights()
{
	register int r, c;
	for (r = 0; r < 8; r++) {
		for (c = 0; c < 8; c++) {
			if (PIECE(r,c) != 'N') continue;
			MARK(r - 2, c - 1);
			MARK(r - 2, c + 1);
			MARK(r - 1, c - 2);
			MARK(r - 1, c + 2);
			MARK(r + 1, c - 2);
			MARK(r + 1, c + 2);
			MARK(r + 2, c - 1);
			MARK(r + 2, c + 1);
		}
	}
}

static void kings()
{
	register int r, c;

	for (r = 0; r < 8; r++) {
		for (c = 0; c < 8; c++) {
			if (PIECE(r,c) != 'K') continue;
			MARK(r - 1, c - 1);
			MARK(r - 1, c);
			MARK(r - 1, c + 1);
			MARK(r, c - 1);
			MARK(r, c + 1);
			MARK(r + 1, c - 1);
			MARK(r + 1, c);
			MARK(r + 1, c + 1);
		}
	}
}

static void rooks()
{
	register int r, c, i;

	for (i = 0; i < 64; i++) {
		if (piece[i] != 'R' && piece[i] != 'Q') continue;

		c = COL(i);
		for (r = ROW(i) - 1; FREE(r,c); r--) MARK(r,c);
		for (r = ROW(i) + 1; FREE(r,c); r++) MARK(r,c);

		r = ROW(i);
		for (c = COL(i) - 1; FREE(r,c); c--) MARK(r,c);
		for (c = COL(i) + 1; FREE(r,c); c++) MARK(r,c);
	}
}

static void bishops()
{
	register int r, c, i;

	for (i = 0; i < 64; i++) {
		if (piece[i] != 'B' && piece[i] != 'Q') continue;

		for (r = ROW(i) - 1, c = COL(i) - 1; FREE(r,c); r--, c--)
			MARK(r, c);

		for (r = ROW(i) + 1, c = COL(i) + 1; FREE(r,c); r++, c++)
			MARK(r, c);

		for (r = ROW(i) + 1, c = COL(i) - 1; FREE(r,c); r++, c--)
			MARK(r, c);

		for (r = ROW(i) - 1, c = COL(i) + 1; FREE(r,c); r--, c++)
			MARK(r, c);
	}
}

static int total()
{
	int i, r;

	for (i = 0, r = 0; i < 64; i++)
		if (piece[i] == 0 && !attacked[i])
			r++;

	return r;
}

int main()
{
	static char buf[1024];

	while (gets(buf)) {
		parse(buf);

		pawns();
		knights();
		rooks();
		bishops();
		kings();

		printf("%d\n", total());
	}

	return 0;
}
