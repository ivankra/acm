/* bipartite matcher to check -1 answers */
/* checked -- no changes */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define INF 0x00FFFFFF

int src[16][16], dst[16][16], height, width;
int tab[8][256][256], got[8][256][256], id;

/*---------------------------------------------------------------------------*/
#define MAXM	128
#define MAXN	128

int adj[MAXM][MAXN], deg[MAXM], match_m, match_n;

int match()
{
	static int p[MAXM], s[MAXM], tm[MAXM], tn[MAXN], f, r, z;
	int i, j, k, t;

	for (i = 0; i < match_m; i++)
		tm[i] = -1;

	for (i = 0; i < match_n; i++)
		tn[i] = -1;

	for (r = 0;; r += f) {
		for (i = 0; i < match_m; i++)
			p[i] = (tm[i] < 0) ? i : -1;

		for (f = 0, z = 0; z < match_m; z++) {
			if (tm[z] >= 0) continue;

			for (s[0] = z, t = 1; t > 0;)
				for (i = s[--t], j = 0; j < deg[i]; j++)
					if (tn[k = adj[i][j]] < 0) {
						for (f++, t = 0;; i = p[i]) {
							j = tm[tn[k] = i];
							tm[i] = k;
							if ((k = j) < 0) break;
						}
						break;
					} else if (p[tn[k]] < 0) {
						p[s[t++] = tn[k]] = i;
					}
		}

		if (f == 0)
			return r;
	}
}

int match_check()
{
	int dx[] = { 0, 1, -1, 0, 0 }, dy[] = { 0, 0, 0, 1, -1 };
	int r1, c1, r2, c2, d, x, u[64][64], v[64][64], n1, n2;

	for(x=0,r1=0;r1<height;r1++)for(c1=0;c1<width;c1++)
		if (src[r1][c1]=='.')u[r1][c1]=-1;else u[r1][c1]=x++;
	n1 = x;

	for(x=0,r1=0;r1<height;r1++)for(c1=0;c1<width;c1++)
		if (dst[r1][c1]=='.')v[r1][c1]=-1;else v[r1][c1]=x++;
	n2 = x;

	if (n1 != n2) return 0;

	memset(deg, 0, sizeof(deg));
	match_m = match_n = n1;

	for(r1=0;r1<height;r1++) for(c1=0;c1<width;c1++) for(d=0;d<5;d++) {
		r2 = r1 + dy[d];
		c2 = c1 + dx[d];
		if (r2 < 0 || c2 < 0 || r2 >= height || c2 >= width) continue;
		if (src[r1][c1] == '.' || src[r1][c1] != dst[r2][c2]) continue;
		x = u[r1][c1];
		adj[x][deg[x]++] = v[r2][c2];
	}

	return (match() == n1);
}
/*---------------------------------------------------------------------------*/

int min(int x, int y) { return (x < y) ? x : y; }

int f(int, int, int);

int g(int row, int pdown, int pvac, int col, int ndown, int nvac)
{
#define G(A,B,C) g(row,pdown,pvac,A,B,C)
	int r;

re:	r = INF;

	if (col == width) {
		if (pvac != ((1 << width) - 1)) return INF;

		for (r = 0; r < width; r++)
			if (dst[row][r] == '.' && ((nvac >> r) & 1) == 0)
				nvac |= 1 << r;

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
		r = min(r, G(col+1, ndown, nvac | (1 << col)));
	}

	/* left */
	if (col > 0 && dst[row][col-1] == src[row][col] &&
	    ((nvac >> (col - 1)) & 1) == 0) {
		if (((pdown >> col) & 1) == 0 && ((nvac >> col) & 1))
			r = min(r, 1 + G(col+1, ndown, nvac | (1 << (col-1))));
		else
			r = min(r, G(col+1, ndown, nvac | (1 << (col-1))));
	}

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

	got[row][pdown][pvac] = id;
	return (tab[row][pdown][pvac] = g(row, pdown, pvac, 0, 0, 0));
}

int main()
{
	int i, j, c, t;

	scanf("%d", &t);

	memset(got, 0, sizeof(got));
	for (id = 1; id <= t; id++) {
		i = scanf("%d %d", &width, &height);
		assert(i == 2);
		assert(1 <= width && width <= 8 && 1 <= height && height <= 8);

		memset(src, 0, sizeof(src));
		memset(dst, 0, sizeof(dst));

		for (i = 0; i < height; i++) {
			for (j = 0; j < width && (c = getchar()) != EOF;)
				if (strchr("XOxo.", c) != NULL) src[i][j++] = toupper(c);
			assert(j == width);
			for (j = 0; j < width && (c = getchar()) != EOF;)
				if (strchr("XOxo.", c) != NULL) dst[i][j++] = toupper(c);
			assert(j == width);
		}

		i = f(0, 0, (1 << width) - 1);

		if (i < INF) { assert(0 <= i && i <= 32); }

		printf("%d\n", (i < INF) ? i : -1);

if (i < INF) {
  assert(match_check());
} else {
  assert(!match_check());
}
	}

	return 0;
}
