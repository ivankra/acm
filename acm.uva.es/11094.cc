#include <cstdio>

char Map[32][32];
int R, C, CurY, CurX, Land;

int dfs(int y, int x) {
	if (y < 0 || y >= R) return 0;
	if (x < 0 || x >= C) { x = (x + C*C) % C; }
	if (Map[y][x] != Land) return 0;

	Map[y][x] = 0;
	return 1 + dfs(y+1, x) + dfs(y-1, x) + dfs(y, x-1) + dfs(y, x+1);
}

int main() {
	while (scanf("%d %d", &R, &C) == 2) {
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				scanf(" %c", &Map[i][j]);
			}
		}
		scanf("%d %d", &CurY, &CurX);
		Land = Map[CurY][CurX];

		dfs(CurY, CurX);

		int best = 0;
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				if (Map[i][j] == Land)
					best >?= dfs(i, j);
		printf("%d\n", best);
	}
}
