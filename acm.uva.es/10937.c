#include <stdio.h>
#include <string.h>

int d[16][16], tr[16][2], got[12][2048], tab[12][2048], n, id=42;
int map[64][64], str[64][64], width, height;

int f(int s, int m)
{
	int i, j;

	if (got[s][m] == id) return tab[s][m];
	got[s][m] = id;

	if ((m + 1) == (1 << n))
		return (tab[s][m] = d[s][0]);

	for (tab[s][m] = 0x7FFFFFFF, i = 0; i < n; i++) {
		if ((m >> i) & 1) continue;
		j = d[s][i] + f(i, m ^ (1 << i));
		if (j < tab[s][m]) tab[s][m] = j;
	}

	return tab[s][m];
}

int bfs(int w)
{
	static int dx[] = { 1, -1, 0, 0 }, dy[] = { 0, 0, 1, -1 };
	static int a[64][64], q[4096][2];
	int i, h, t, x, y;

	for (i = 0; i <= height; i++)
		for (t = 0; t <= width; t++)
			a[i][t] = 0;

	a[q[0][0]=tr[w][0]][q[0][1]=tr[w][1]] = 1;

	for (h = 0, t = 1; h < t; h++) {
		for (i = 0; i < 4; i++) {
			x = q[h][0] + dx[i]; y = q[h][1] + dy[i];
			if (map[x][y] && a[x][y] == 0) {
				a[x][y] = a[q[h][0]][q[h][1]] + 1;
				q[t][0] = x; q[t][1] = y; t++;
			}
		}
	}

	for (i = 0; i < n; i++) {
		x = tr[i][0]; y = tr[i][1];
		if (a[x][y] == 0) return 1;
		d[w][i] = a[x][y] - 1;
	}

	return 0;
}

int solve()
{
	int i, j, k;

	memset(map, 0, sizeof(map));
	for (i = 1; i <= height; i++)
		for (j = 1; j <= width; j++)
			if (strchr(".!@", str[i][j]) != NULL) map[i][j] = 1;

	for (i = 1; i <= height; i++)
		for (j = 1; j <= width; j++)
			if (str[i][j] == '*') {
				map[i-1][j-1] = map[i-1][j] = map[i-1][j+1] = 0;
				map[i][j-1] = map[i][j] = map[i][j+1] = 0;
				map[i+1][j-1] = map[i+1][j] = map[i+1][j+1] = 0;
			}

	for (n = k = 0, i = 1; i <= height; i++)
		for (j = 1; j <= width; j++)
			if (str[i][j] == '@' || str[i][j] == '!') {
				if (map[i][j] == 0) return -1;
				if (str[i][j] == '@') k++;
				tr[n][0] = i; tr[n][1] = j; n++;
			}

	if (k != 1)
		return -1;

	for (i = 0; i < n; i++)
		if (bfs(i)) return -1;

	id++;
	return f(0, 1);
}

int main()
{
	int i, j, k;

	while (scanf("%d %d", &height, &width) == 2 && height > 0) {
		for (i = 1; i <= height; i++)
			for (j = 1; j <= width && (k = getchar()) != EOF;)
				if (strchr("@~#.*!", k) != NULL) str[i][j++] = k;
		printf("%d\n", solve());
	}

	return 0;
}
