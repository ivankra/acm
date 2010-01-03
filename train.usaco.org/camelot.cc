/*
ID: infnty1
PROB: camelot
LANG: C++
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define INF 0x00FFFFFF

struct loc { int y, x, v; };

int nrows, ncols, nv, nk;
int dist[1056][1056], sum[2048];
loc K[2048];

int get(loc *l)
{
	char c;
	if (scanf(" %c %d", &c, &l->y) != 2) return 0;
	l->y--;
	l->x = toupper(c) - 'A';
	l->v = l->y * ncols + l->x;
	return 1;
}

void bfs(int y0, int x0)
{
	static loc a[2048];
	static int dx[] = { 1, 1,  2, 2, -1, -1, -2, -2 };
	static int dy[] = { 2, -2, 1, -1, 2, -2,  1, -1 };
	int *d, i, j, n, m;

	a[0].v = y0 * ncols + x0;
	d = dist[a[0].v];
	a[0].y = y0;
	a[0].x = x0;
	for (i = 0; i < nv; i++) d[i] = INF;
	d[a[0].v] = 0;
	for (n = 0, m = 1; n < m; n++) {
		for (i = 0; i < 8; i++) {
			int y = a[n].y + dy[i], x = a[n].x + dx[i];
			if (y < 0 || x < 0 || y >= nrows || x >= ncols) continue;
			j = y * ncols + x;
			if (d[j] < INF) continue;
			a[m].y = y;
			a[m].x = x;
			d[a[m++].v = j] = d[a[n].v] + 1;
		}
	}
}

int check(loc X)
{
	int F, N, i, r=INF;
	int d = (abs(K[0].x-X.x) >? abs(K[0].y-X.y));

	for (F = 0; F < nv; F++) {
		for (i = 1; i <= nk; i++) {
			N = K[i].v;
			r <?= d + dist[N][X.v] + dist[F][X.v] + sum[F] - dist[F][N];
		}
	}
	return r;
}

int main()
{
	freopen("camelot.in", "r", stdin);
	freopen("camelot.out", "w", stdout);

	scanf("%d %d", &nrows, &ncols);
	get(&K[0]);
	for (nk = 0; get(&K[nk+1]); nk++);
	nv = nrows * ncols;

	for (int i = 0; i < nrows; i++)
		for (int j = 0; j < ncols; j++)
			bfs(i, j);

	for (int i = 0; i < nv; i++) {
		sum[i] = 0;
		for (int j = 1; j <= nk; j++) {
			sum[i] += dist[i][K[j].v];
			if (sum[i] >= INF) { sum[i]=INF; break; }
		}
	}

	int r = INF;
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++) {
			loc X={K[0].y+i,K[0].x+j,0};
			if (X.x<0 || X.y<0 || X.x>=ncols || X.y>=nrows) continue;
			X.v = X.y * ncols + X.x;
			r <?= check(X);
		}

	for (int i = 0; i < nrows; i++)
		for (int j = 0; j < ncols; j++)
			r <?= sum[i*ncols+j] + (abs(K[0].y-i) >? abs(K[0].x-j));

	printf("%d\n", r);

	return 0;
}
