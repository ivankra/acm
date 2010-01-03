// MST
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

int nrows, ncols, N, posy[128], posx[128], dist[128][128];
char maze[64][64];

int pop(queue<int> &q) { int r = q.front(); q.pop(); return r; }

int main() {
	int T, N;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &ncols, &nrows);
		memset(maze, '#', sizeof(maze));
		N = 0;
		for (int i = 1; i <= nrows; i++) {
			for (int j = 1; j <= ncols; j++) {
				int c;
				while ((c = getchar()) == '\n' || c == '\r');
				maze[i][j] = c;

				if (c == 'S' || c == 'A') {
					posy[N] = i;
					posx[N] = j;
					N++;
				}
			}
		}

		for (int i = 0; i < N; i++) {
			int d[64][64];
			memset(d, 0x3f, sizeof(d));
			d[posy[i]][posx[i]] = 0;

			queue<int> q; q.push(posy[i]); q.push(posx[i]);
			while (!q.empty()) {
				int y = pop(q); int x = pop(q);
				for (int i = 0; i < 4; i++) {
					int y1 = y + "0211"[i] - '1';
					int x1 = x + "1102"[i] - '1';
					if (maze[y1][x1] == '#') continue;
					if (d[y][x]+1 < d[y1][x1]) {
						d[y1][x1] = d[y][x] + 1;
						q.push(y1); q.push(x1);
					}
				}
			}

			for (int j = 0; j < N; j++)
				dist[i][j] = d[posy[j]][posx[j]];
		}

		int res = 0, cov[128];
		memset(cov, 0, sizeof(cov));
		cov[0] = 1;

		for (;;) {
			int u = -1;
			for (int v = 0; v < N; v++)
				if (!cov[v] && (u<0 || dist[0][v] < dist[0][u])) u = v;
			if (u < 0) break;

			res += dist[0][u];
			cov[u] = 1;
			for (int v = 0; v < N; v++)
				dist[0][v] <?= dist[v][u];
		}
		printf("%d\n", res);
	}
}
