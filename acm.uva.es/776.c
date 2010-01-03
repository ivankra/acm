#include <stdio.h>
#include <string.h>

#define MAXROWS 128
#define MAXCOLS 128

static char map[MAXROWS][MAXCOLS];
static int assign[MAXROWS][MAXCOLS];
static int st[8096];
static int width, height;

static void segv() { char *p; for (p = NULL;;) *p++ = 42; }
static void outl() { char buf[1024]; for (;;) write(1, buf, sizeof(buf)); }

static void fill(int x, int y, int c)
{
	int stp;
	char m;

	stp = 0;
	st[stp++] = x;
	st[stp++] = y;
	m = map[y][x];
	assign[y][x] = c;

	while (stp >= 2) {
		y = st[--stp];
		x = st[--stp];

#define GO(Y,X) if (map[Y][X] == m && assign[Y][X] == 0) \
		      { assign[Y][X] = c; st[stp++] = (X); st[stp++] = (Y); }

		if (y > 0) {
			if (x > 0) GO(y - 1, x - 1);
			GO(y - 1, x);
			if ((x + 1) < width) GO(y - 1, x + 1);
		}

		if (x > 0) GO(y, x - 1);
		if ((x + 1) < width) GO(y, x + 1);

		if ((y + 1) < height) {
			if (x > 0) GO(y + 1, x - 1);
			GO(y + 1, x);
			if ((x + 1) < width) GO(y + 1, x + 1);
		}
#undef GO
	}
}

int main()
{
	static int alph[256], w[MAXCOLS+1];
	int i, j, c;

	for (i = 0; i < 256; i++)
		alph[i] = ((i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z'));

	for (;;) {
		memset(map, 0, sizeof(map));

		for (height = width = 0, i = 0; (c = getchar()) != EOF;) {
			if (alph[c] != 0) {
				map[height][i++] = c;
				if (i >= MAXCOLS) segv();
			} else if (c == '\n') {
				if (i == 0)
					continue;

				if (width == 0)
					width = i;

				height++;
				i = 0;

				if (height >= MAXROWS) outl();
			} else if (c == '%') {
				break;
			}
		}

		if (i != 0) {
			if (width == 0) width = i;
			height++;
		}

		if (width == 0 || height == 0)
			break;

		memset(assign, 0, sizeof(assign));

		for (i = 0, c = 0; i < height; i++)
			for (j = 0; j < width; j++)
				if (assign[i][j] == 0)
					fill(j, i, ++c);

		for (i = 0; i < width; i++) {
			for (c = assign[0][i], j = 1; j < height; j++)
				if (assign[j][i] > c) c = assign[j][i];

			for (j = 0; c > 0; j++, c /= 10);

			w[i] = j;
		}

		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++)
				printf((j + 1) >= width ? "%*d\n" : "%*d ",
				       w[j], assign[i][j]);
		}
		printf("%%\n");
	}

	return 0;
}
