#include <stdio.h>
#include <string.h>

int n, m, r;
int walls[8][8], attack[8][8];

void solve(int y, int x)
{
	static int dx[] = { 1, -1, 0, 0 }, dy[] = { 0, 0, 1, -1 };
	int i, j;

	if (x > n) {
		y++;
		x = 1;
	}

	if (y > n) {
		if (r > m) m = r;
		return;
	}

	solve(y, x + 1);

	if (walls[y][x] || attack[y][x])
		return;

	for (i = 0; i < 4; i++)
		for (j = 0; walls[y + j * dy[i]][x + j * dx[i]] == 0; j++)
			attack[y + j * dy[i]][x + j * dx[i]]++;

	r++;
	solve(y, x + 1);
	r--;

	for (i = 0; i < 4; i++)
		for (j = 0; walls[y + j * dy[i]][x + j * dx[i]] == 0; j++)
			attack[y + j * dy[i]][x + j * dx[i]]--;
}

int main()
{
	int i, j, c;

	while (scanf("%d", &n) == 1 && n > 0) {
		memset(walls, 1, sizeof(walls));
		memset(attack, 0, sizeof(attack));

		for (i = 1; i <= n; i++)
			for (j = 1; j <= n && (c = getchar()) != EOF;)
				if (c == '.')
					walls[i][j++] = 0;
				else if (c == 'X')
					j++;

		m = r = 0;
		solve(1, 1);
		printf("%d\n", m);
	}

	return 0;
}
