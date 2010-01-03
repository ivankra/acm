#include <cstdio>

char maze[1024][1024];
int best;

int dfs(int y, int x)
{
	if (maze[y][x] != '.')
		return -999999;

	maze[y][x] = '#';

	int a = 0, b = 0;
	for (int dir = 0; dir < 4; dir++) {
		int t = 1 + dfs(y + "1102"[dir]-'1', x + "0211"[dir]-'1');
		if (t >= a) {
			b = a;
			a = t;
		} else if (t > b) {
			b = t;
		}
	}

	best >?= a + b;
	return a;
}

int main()
{
	int T, R, C;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &C, &R);
		for (int i = 1; i <= R; i++) {
			for (int j = 1; j <= C; j++) {
				for (;;) {
					int c = getchar();
					if (c == '#' || c == '.') {
						maze[i][j] = c;
						break;
					}
				}
			}
		}

		for (int i = 0; i <= R+1; i++)
			maze[i][0] = maze[i][C+1] = '#';

		for (int i = 0; i <= C+1; i++)
			maze[0][i] = maze[R+1][i] = '#';

		best = 0;
		for (int i = 1; i <= R; i++)
			for (int j = 1; j <= C; j++)
				if (maze[i][j] == '.')
					dfs(i, j);
		printf("Maximum rope length is %d.\n", best);
	}
}
