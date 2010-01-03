#include <stdio.h>
#include <string.h>

int map[32][32], n;
int n;

int dfs(int x, int y)
{
	if (map[x][y]-- < 1)
		return 0;

	return (1 + dfs(x - 1, y - 1) + dfs(x, y - 1) + dfs(x + 1, y - 1) +
		dfs(x - 1, y) + dfs(x + 1, y) + dfs(x - 1, y + 1) +
		dfs(x, y + 1) + dfs(x + 1, y + 1));
}

int solve()
{
	int i, j, k, c;

	memset(map, 0, sizeof(map));

	for (n = 0; (c = getchar()) != EOF;)
		if (c == '0' || c == '1')
			map[1][++n] = c - '0';
		else if (c == '\n' && n > 0)
			break;

	for (i = 2; i <= n; i++)
		for (j = 1; j <= n && (c = getchar()) != EOF;)
			if (c == '0' || c == '1') map[i][j++] = c - '0';

	for (i = 1, c = 0; i <= n; i++)
		for (j = 1; j <= n; j++)
			if (map[i][j] && (k = dfs(i, j)) > c) c = k;

	return c;
}

int main()
{
	int t;

	for (scanf("%d", &t); t-- > 0;)
		printf(t ? "%d\n\n" : "%d\n", solve());

	return 0;
}
