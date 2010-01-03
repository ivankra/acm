#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

char grid[64][64];
int nrows, ncols;

int dx[]={1,-1,0,0}, dy[]={0,0,1,-1};

int bfs(int sy, int sx) {
	static int Q[64*64*2];
	static int dist[64][64];
	int *head = Q, *tail = Q;

	for (int y = 1; y <= nrows; y++)
		for (int x = 1; x <= ncols; x++)
			dist[y][x] = 0x3fffffff;

	dist[sy][sx] = 0;
	*tail++ = sy;
	*tail++ = sx;

	while (head < tail) {
		int y = *head++;
		int x = *head++;
		if (grid[y][x] == 'X') return dist[y][x];
		for (int dir = 0; dir < 4; dir++) {
			int y1 = y + dy[dir];
			int x1 = x + dx[dir];
			if (grid[y1][x1] == 'X')
				return 1 + dist[y][x];
			else if (grid[y1][x1] != '#' && dist[y1][x1] > 1 + dist[y][x]) {
				dist[y1][x1] = 1 + dist[y][x];
				*tail++ = y1;
				*tail++ = x1;
			}
		}
	}

	return 0x3fffffff;
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &nrows, &ncols);
		memset(grid, '#', sizeof(grid));

		int sy = 0, sx = 0;
		for (int i = 1; i <= nrows; i++) {
			for (int j = 1; j <= ncols; j++) {
				scanf(" %c", &grid[i][j]);
				if (grid[i][j] == 'E') { sy = i; sx = j; }
			}
		}

		static int f[64][64], g[64][64][4];
		for (int y = 1; y <= nrows; y++) {
			for (int x = 1; x <= ncols; x++) {
				for (int d = 0; d < 4; d++) {
					int y1 = y + dy[d];
					int x1 = x + dx[d];
					if (grid[y][x] == 'X' || grid[y1][x1] == 'X')
						g[y][x][d] = 0;
					else if (grid[y1][x1] == '#')
						g[y][x][d] = 0x3fffffff;
					else {
						char c = grid[y1][x1];
						grid[y1][x1] = '#';
						g[y][x][d] = bfs(y, x);
						grid[y1][x1] = c;
					}
				}
			}
		}

		memset(f, 0x3f, sizeof(f));
		for (;;) {
			bool changed = false;
			for (int y = 1; y <= nrows; y++) {
				for (int x = 1; x <= ncols; x++) {
					if (grid[y][x] == '#') continue;

					int t = f[y][x];
					if (grid[y][x] == 'X') t = 0;

					for (int dir = 0; dir < 4; dir++) {
						if (grid[y + dy[dir]][x + dx[dir]] == '#') continue;
						t <?= max(g[y][x][dir], 1 + f[y + dy[dir]][x + dx[dir]]);
					}
					
					if (t < f[y][x]) {
						f[y][x] = t;
						changed = true;
					}
				}
			}
			if (!changed) break;
		}

		printf("%d\n", f[sy][sx]);
	}
}
