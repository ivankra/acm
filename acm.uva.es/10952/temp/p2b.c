#include <stdio.h>
#include <string.h>
#include <assert.h>

#define INF 0x0FFFFFFF

int src[16][16], dst[16][16], height, width;
int tab[8][256][256], got[8][256][256], id;

int min(int x, int y) { return (x < y) ? x : y; }

char *bin(int x) {
	static char b[16][16]; static int z=0;
	int i;
	z = (z + 1) % 16;
	for (i = 0; i < 8; i++)
		b[z][i] = ((x >> i) & 1) + '0';
	b[z][8] = 0;
	return b[z];
}

int f(int row, int mdown, int mbusy);

/*
nvac:   * . *  *  *  .  *
ndown:  |            |
        x . o  x  o  x  .
*/

#define G(A,B,C) g(row,pdown,pvac,A,B,C)

int g(int row, int pdown, int pvac, int col, int ndown, int nvac)
{
	int r = INF;

re:
/*printf("g(row=%d,pdown=%s,pvac=%s, col=%d,ndown=%s,nvac=%s)\n",
       row,bin(pdown),bin(pvac),col,bin(ndown),bin(nvac));*/

	if (col == width) {
		if (pvac != ((1 << width) - 1)) return INF;

		for (r = 0; r < width; r++)
			if (dst[row][r] == '.' && ((nvac >> r) & 1) == 0)
				nvac |= 1 << r;

/*printf("** g transition: pvac'=%s\n", bin(pvac));*/

		return f(row+1, ndown, nvac);
	}

	if (src[row][col] == '.') {
		if ((pdown >> col) & 1) {
			if (nvac & (1 << col)) return INF;
			nvac |= 1 << col;
		}

		if (((pvac >> col) & 1) == 0)
			return INF;

		if (dst[row][col] == '.')
			nvac |= 1 << col;

		col++;
		goto re;
	}

	if ((pdown >> col) & 1) {
		if (nvac & (1 << col)) return INF;
		nvac |= (1 << col);
	}

	if (((pvac >> col) & 1) == 0) {
		/* must move up */
		if (dst[row-1][col] != src[row][col]) return INF;

		if ((pdown >> col) & 1) {
			return 1 + g(row, pdown, pvac | (1 << col), col+1, ndown, nvac);
		} else {
			pvac |= 1 << col;
			col++;
			goto re;
		}
	}

	if (src[row][col] == dst[row][col] && ((pdown >> col) & 1) == 0 &&
	    ((nvac >> col) & 1) == 0) {
		/* remain */
		r = G(col+1, ndown, nvac | (1 << col));
	}

	/* left */
	if (col > 0 && dst[row][col-1] == src[row][col] &&
	    ((nvac >> (col - 1)) & 1) == 0)
		r = min(r, G(col+1, ndown, nvac | (1 << (col-1))) + ((nvac >> col) & 1));

	/* right */
	if (dst[row][col+1] == src[row][col])
		r = min(r, G(col+1, ndown, nvac | (1 << (col+1))));

	/* down */
	if (dst[row+1][col] == src[row][col])
		r = min(r, G(col+1, ndown | (1 << col), nvac));

	return r;
}

int f(int row, int pdown, int pvac)
{
	if (row == height)
		return (pdown == 0 && pvac == ((1 << width) - 1)) ? 0 : INF;

	if (got[row][pdown][pvac] == id)
		return tab[row][pdown][pvac];
/*printf("f(row=%d,pdown=%s,pvac=%s)\n", row, bin(pdown), bin(pvac));*/

	got[row][pdown][pvac] = id;
	return (tab[row][pdown][pvac] = g(row, pdown, pvac, 0, 0, 0));
}

int main()
{
	int i, j, c, t;

	memset(got, 0, sizeof(got));
	id = 1;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &width, &height) == 2;) {
		assert(1 <= width && width <= 8 && 1 <= height && height <= 8);

		memset(src, 0, sizeof(src));
		memset(dst, 0, sizeof(dst));

		for (i = 0; i < height; i++) {
			for (j = 0; j < width && (c = getchar()) != EOF;)
				if (strchr("XO.", c) != NULL) src[i][j++] = c;
			for (j = 0; j < width && (c = getchar()) != EOF;)
				if (strchr("XO.", c) != NULL) dst[i][j++] = c;
		}

		id++;
		i = f(0, 0, (1 << width) - 1);
		printf("%d\n", (i < INF) ? i : -1);
	}

	return 0;
}
