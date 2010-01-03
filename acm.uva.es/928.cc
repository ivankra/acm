#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

#define INF 100000000

int N, M;
char maze[310][310];

int start_y, start_x;
int end_y, end_x;

int dist[310][310][3];
int buffer[(300*300*3+1000)*3], *head, *tail;

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i <= N+1; i++) maze[i][0] = maze[i][M+1] = '#';
		for (int i = 0; i <= M+1; i++) maze[0][i] = maze[N+1][i] = '#';
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				scanf(" %c", &maze[i][j]);
				if (maze[i][j] == 'S') {
					start_y = i;
					start_x = j;
				}
				if (maze[i][j] == 'E') {
					end_y = i;
					end_x = j;
				}
			}
		}

		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				for (int k = 0; k < 3; k++)
					dist[i][j][k] = INF;

		head = tail = buffer;
		*tail++ = start_y;
		*tail++ = start_x;
		*tail++ = 0;
		dist[start_y][start_x][0] = 0;

		while (head != tail) {
			int y0 = *head++;
			int x0 = *head++;
			int m = *head++;

			for (int dir = 0; dir < 4; dir++) {
				int dy = "1102"[dir] - '1';
				int dx = "0211"[dir] - '1';
				int y = y0, x = x0;
				int d, mm;

				for (int k = 0; k <= m; k++) {
					y += dy;
					x += dx;
					if (maze[y][x] == '#') goto skip;
				}

				d = 1 + dist[y0][x0][m];
				mm = (m + 1) % 3;

				if (d < dist[y][x][mm]) {
					dist[y][x][mm] = d;
					*tail++ = y;
					*tail++ = x;
					*tail++ = mm;

					if (y == end_y && x == end_x) {
						printf("%d\n", d);
						goto done;
					}
				}

skip:;
			}

		}

		printf("NO\n");
done:;
	}
}
