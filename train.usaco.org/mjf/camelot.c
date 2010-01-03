/*
ID: mjf28791
PROG: camelot
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>

#define INF 0xFFFFFF

int nrows, ncols, ncells, best, nknights, kingx, kingy;
int dist[1056][1056], knights[2048];

int kingmoves(int dx, int dy)
{
	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;

	if (dx > dy)
		return dx;
	else
		return dy;
}

void solve(int y0, int x0)
{
	int i, j, k, s, t, z, dx, dy;

	z = y0 * ncols + x0;
	for (s = 0, i = 0; i < nknights; i++) {
		if (dist[knights[i]][z] == INF) return;
		s += dist[knights[i]][z];
	}
	if (s >= best) return;

	t = s + kingmoves(kingx - x0, kingy - y0);
	if (t < best) best = t;

	for (dx = -1; dx <= 1; dx++) {
		if ((kingx + dx) < 0 || (kingx + dx) >= ncols) continue;

		for (dy = -1; dy <= 1; dy++) {
			if ((kingy + dy) < 0 || (kingy + dy) >= nrows) continue;

			i = (kingy + dy) * ncols + kingx + dx;
			j = kingmoves(dx, dy);

			for (k = 0; k < nknights; k++) {
				if (dist[knights[k]][i] == INF) continue;
				t = dist[knights[k]][i] + dist[i][z] + j +
				    s - dist[knights[k]][z];
				if (t < best) best = t; 
			}
		}
	}
}

void makedist(int y, int x)
{
	static int qy[2048], qx[2048];
	int i, d, s, h, t;

	s = y * ncols + x;
	qx[0] = x;
	qy[0] = y;
	dist[s][y * ncols + x] = 0;
	t = 1;
	h = 0;

	for (h = 0, t = 1; h < t; h++) {
		d = dist[s][qy[h] * ncols + qx[h]] + 1;
		for (i = 0; i < 8; i++) {
			x = qx[h] + "00113344"[i] - '2';
			y = qy[h] + "13040413"[i] - '2';

			if (0 <= x && x < ncols && 0 <= y && y < nrows &&
			    dist[s][y * ncols + x] == INF) {
				dist[s][y * ncols + x] = d;
				qy[t] = y;
				qx[t] = x;
				t++;
			}
		}
	}
}

int main()
{
	int i, j, k, r;
	char c;

	freopen("camelot.in", "r", stdin);
	freopen("camelot.out", "w", stdout);

	scanf("%d %d", &nrows, &ncols);
	ncells = nrows * ncols;

	for (i = 0; i < ncells; i++)
		for (j = 0; j < ncells; j++)
			dist[i][j] = INF;

	for (i = 0; i < nrows; i++)
		for (j = 0; j < ncols; j++)
			makedist(i, j);

	scanf(" %c %d", &c, &r);
	kingx = c - 'A';
	kingy = r - 1;

	for (nknights = 0; scanf(" %c %d", &c, &r) == 2;)
		knights[nknights++] = (r - 1) * ncols + c - 'A';

	best = INF;
	for (i = 0; i < nrows; i++)
		for (j = 0; j < ncols; j++)
			solve(i, j);

	printf("%d\n", best);

	return 0;
}
