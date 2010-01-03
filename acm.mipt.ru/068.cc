// (solution through bipartite matching)
#include <cstdio>
#include <cstring>

int N, match[32][32], seen[32][32];
char Map[32][32];

int dfs(int y, int x) {
	if (seen[y][x]++) return 0;
	for (int d = 0; d < 4; d++) {
		int Y = y + "0211"[d] - '1', X = x + "1102"[d] - '1';
		if (Map[Y][X] == '#') continue;
		if (match[Y][X] < 0 || dfs(match[Y][X]>>8, match[Y][X]&0xff)) {
			match[Y][X] = (y << 8) + x;
			match[y][x] = (Y << 8) + X;
			return 1;
		}
	}
	return 0;
}

int main() {
	scanf("%d", &N);
	memset(Map, '#', sizeof(Map));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			scanf(" %c", &Map[i][j]);

	int res = 0;

	memset(match, 0xff, sizeof(match));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (Map[i][j]=='#' || ((i+j)&1)==1) continue;
			memset(seen, 0, sizeof(seen));
			res += dfs(i, j);
		}
	}
	printf("%d\n", res);
}
