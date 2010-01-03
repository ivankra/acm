#include <stdio.h>
#include <string.h>

#define INF 0x3FFFFFFF

int map[128][128], door[128][128], n, m;
int dx[] = { 0, -1, 1, 0 }, dy[] = { -1, 0, 0, 1 }, D[256];

int heap[16384], dist[16384], loc[16384], heapn;

int cell(int r, int c) { return r * m + c; }

void up(int p)
{
	int x;
	for (x = heap[p]; p > 1 && dist[x] < dist[heap[p >> 1]]; p >>= 1)
		loc[heap[p] = heap[p >> 1]] = p;
	loc[heap[p] = x] = p;
}

void down(int p)
{
	int x, t;

	for (; (p << 1) <= heapn; p = x) {
		x = (dist[heap[p << 1]] < dist[heap[p]]) ? (p << 1) : p;
		if ((p<<1)+1 <= heapn && dist[heap[(p<<1)+1]] < dist[heap[x]])
			x = (p << 1) + 1;
		if (x == p) break;
		t = heap[p];
		loc[heap[p] = heap[x]] = p;
		loc[heap[x] = t] = x;
	}
	loc[heap[p]] = p;
}

int solve()
{
	int i, j, s, y, x, y1, x1, d;

	j = m * n;
	for (i = 0; i <= j; i++) dist[i] = INF;

	heapn = 1;
	dist[heap[1] = cell(n-1,0)] = 0;
	loc[cell(n-1,0)] = 1;

	while (heapn > 0) {
		s = heap[1];
		if (--heapn >= 1) {
			heap[1] = heap[heapn+1];
			down(1);
		}

		y = s / m;
		x = s % m;
		if (y == 0 && x == m-1) break;

		for (d = 0; d < 4; d++) {
			y1 = y + dy[d];
			x1 = x + dx[d];
			if (y1 < 0 || y1 >= n) continue;
			if (x1 < 0 || x1 >= m) continue;
			if (map[y1][x1] == '#') continue;

			i = D[map[y1][x1]];
			if (i >= 0 && d != 3-i) continue;

			if (map[y][x] == '.') {
				i = 1;
			} else {
				if (D[map[y][x]] == d)
					i = 1;
				else if (D[map[y][x]] == 3-d)
					i = 1 + 2 * door[y][x];
				else
					i = 1 + door[y][x];
			}

			j = y1*m+x1;
			if (dist[j] <= dist[s]+i) continue;

			if (dist[j] == INF) {
				heap[++heapn] = j;
				loc[j] = heapn;
			}

			dist[j] = dist[s] + i;
			up(loc[j]);
		}
	}

	return dist[m-1];
}

int main()
{
	int i, j, k, t;

	for (i = 0; i < 256; i++) D[i] = -1;
	D['N']=0; D['W']=1; D['E']=2; D['S']=3;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		for (i = 0; i < n; i++)
			for (j = 0; j < m && (k = getchar()) != EOF;)
				if (strchr(".#NWES", k) != NULL) map[i][j++] = k;

		for (i = 0; i < n; i++)
			for (j = 0; j < m; j++)
				if (D[map[i][j]] >= 0) scanf("%d", &door[i][j]);

		i = solve();
		printf((i >= INF) ? "Poor Kianoosh\n" : "%d\n", i);
	}

	return 0;
}
