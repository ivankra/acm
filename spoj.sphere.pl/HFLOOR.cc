#include <stdio.h>
#include <string.h>

int f[128][128], n, m;
int npeople, nrooms;

static void dfs(int y, int x)
{
	f[y][x] = 0;
	for (int d = 0; d < 4; d++) {
		int y1 = y + "1021"[d] - '1';
		int x1 = x + "0112"[d] - '1';
		if (f[y1][x1]) dfs(y1, x1);
	}
}

int main()
{
	int i, j, c, T;

	scanf("%d", &T);
	while (T-- > 0 && scanf("%d %d", &m, &n) == 2) {
		memset(f, 0, sizeof(f));
		npeople = 0;
		for (i = 1; i <= m; i++) {
			for (j = 1; j <= n; j++) {
				while ((c = getchar()) != EOF)
					if (c == '#') {
						break;
					} else if (c == '*') {
						f[i][j] = 1;
						npeople++;
						break;
					} else if (c == '-') {
						f[i][j] = 1;
						break;
					}
			}
		}

		c = 0;
		for (i = 1; i <= m; i++)
			for (j = 1; j <= n; j++)
				if (f[i][j]) c++, dfs(i,j);
		printf("%.2f\n", (double)npeople / (double)c);
	}
	

	return 0;
}
