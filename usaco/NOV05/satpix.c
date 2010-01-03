/*
ID: infnty1
LANG: C
TASK: satpix
*/
/* Algorithm: DFS. */
#include <stdio.h>
#include <assert.h>

int map[1024][82], W, H, Y[80001], X[80001];
int dx[] = { 1, -1, 0, 0 }, dy[] = { 0, 0, 1, -1 };

int scan(int y, int x)
{
	int i, n, r;

	map[Y[0] = y][X[0] = x] = 0;
	r = n = 1;

	while (n-- > 0) {
		y = Y[n];
		x = X[n];
		for (i = 0; i < 4; i++) {
			if (map[y+dy[i]][x+dx[i]] != 1) continue;
			map[Y[n]=y+dy[i]][X[n]=x+dx[i]] = 0; n++; r++;
		}
	}

	return r;
}

int max(int x, int y)
{
	return (x > y) ? x : y;
}

int main()
{
	int i, j, c;

	freopen("satpix.in", "r", stdin);
	freopen("satpix.out", "w", stdout);

	scanf("%d %d", &W, &H);
	assert(1 <= W && W <= 80 && 1 <= H && H <= 1000);

	for (i = 0; i <= W; i++) map[0][i] = map[H+1][i] = 0;

	for (i = 1; i <= H; i++) {
		map[i][0] = map[i][W+1] = 0;
		for (j = 1; j <= W && (c = getchar()) != EOF;)
			if (c == '.') map[i][j++] = 0;
			else if (c == '*') map[i][j++] = 1;
	}

	for (c = 0, i = 1; i <= H; i++)
		for (j = 1; j <= W; j++)
			if (map[i][j]) c = max(c, scan(i, j));

	printf("%d\n", c);
	fflush(stdout);

	return 0;
}
