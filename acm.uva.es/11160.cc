#include <algorithm>
#include <vector>
#include <sstream>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cctype>
using namespace std;

char maze[16][16];
bool canMove[16*16][3][3], exitCell[16*16];
int N;

int d[81*81*81+1000];
int q[81*81*81*3+1000];

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		assert(3 <= N && N <= 9);

		int head = 0, tail = 0;

		memset(maze, '#', sizeof(maze));
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf(" %c", &maze[i][j]);
				if (isalpha(maze[i][j]) && maze[i][j] != 'X')
					q[tail++] = (i-1)*9+(j-1);
			}
		}

		memset(canMove, 0, sizeof(canMove));
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++) {
				int cell = (i-1)*9 + (j-1);
				exitCell[cell] = (maze[i][j]=='X');

				for (int dx = -1; dx <= 1; dx++)
					for (int dy = -1; dy <= 1; dy++)
						canMove[cell][dy+1][dx+1] = (maze[i+dy][j+dx] != '#');
			}
		}

		sort(q, q+tail);

		memset(d, 0, sizeof(d));
		d[q[0]*81*81 + q[1]*81 + q[2]] = 1;

		while (head < tail) {
			int s[3], t[3];
			s[0] = q[head++];
			s[1] = q[head++];
			s[2] = q[head++];
			int es = s[0]*81*81 + s[1]*81 + s[2];

			for (int dir = 0; dir < 4; dir++) {
				int dx = "0211"[dir] - '1';
				int dy = "1102"[dir] - '1';

				for (int i = 0; i < 3; i++) {
					t[i] = canMove[s[i]][dy+1][dx+1] ? (s[i] + dx + 9*dy) : s[i];
				}

				for (int i = 1; i < 3; i++)
					for (int j = i; j > 0 && t[j-1] > t[j]; j--)
						swap(t[j-1], t[j]);

				if (t[0] == t[1]) {
					t[0] -= dx + 9*dy;
					if (t[0] == t[2]) continue;
				} else if (t[1] == t[2]) {
					t[1] -= dx + 9*dy;
					if (t[1] == t[0]) continue;
				}

				for (int i = 1; i < 3; i++)
					for (int j = i; j > 0 && t[j-1] > t[j]; j--)
						swap(t[j-1], t[j]);

				if (exitCell[t[0]] && exitCell[t[1]] && exitCell[t[2]]) {
					printf("Case %d: %d\n", cs, d[es]);
					goto done;
				}

				int et = t[0]*81*81 + t[1]*81 + t[2];
				if (d[et] == 0) {
					d[et] = d[es] + 1;
					q[tail++] = t[0];
					q[tail++] = t[1];
					q[tail++] = t[2];
				}
			}

		}

		printf("Case %d: trapped\n", cs);
done:;
	}
}
