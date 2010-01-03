#include <stdio.h>
#include <string.h>

int map[128][128], run[128][128], nr, nc;

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int search(int y, int x)
{
	if (run[y][x] > 0)
		return run[y][x];

	run[y][x] = 1;

	if (map[y - 1][x] < map[y][x])
		run[y][x] = max(run[y][x], 1 + search(y - 1, x));

	if (map[y + 1][x] < map[y][x])
		run[y][x] = max(run[y][x], 1 + search(y + 1, x));

	if (map[y][x - 1] < map[y][x])
		run[y][x] = max(run[y][x], 1 + search(y, x - 1));

	if (map[y][x + 1] < map[y][x])
		run[y][x] = max(run[y][x], 1 + search(y, x + 1));

	return run[y][x];
}

int solve()
{
	int x, y, r;

	memset(run, 0, sizeof(run));

	for (r = 0, y = 1; y <= nr; y++)
		for (x = 1; x <= nc; x++)
			r = max(r, search(y, x));

	return r;
}

int main()
{
	char s[256];
	int i, j, t;

	for (scanf("%d", &t); t-- > 0 && scanf(" %s %d %d", s, &nr, &nc) == 3;) {
		for (i = 0; i <= (nr + 1); i++)
			for (j = 0; j <= (nc + 1); j++)
				map[i][j] = 0x3FFFFFFF;

		for (i = 1; i <= nr; i++)
			for (j = 1; j <= nc; j++)
				scanf("%d", &map[i][j]);

		printf("%s: %d\n", s, solve());
	}

	return 0;
}
