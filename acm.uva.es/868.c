#include <stdio.h>
#include <string.h>
#include <assert.h>

int map[128][128], n, m;
int dy[]={1,-1,0,0}, dx[]={0,0,1,-1}, sol;

void go(int y, int x, int k)
{
	if (y == n) { sol <?= x; return; }

	if (map[y][x] < k) {
		for (int d = 0; d < 4; d++)
			if (map[y+dy[d]][x+dx[d]]==map[y][x]+1)
				go(y+dy[d],x+dx[d],k);
	} else {
		for (int d = 0; d < 4; d++)
			if (map[y+dy[d]][x+dx[d]]==1)
				go(y+dy[d],x+dx[d],k+1);
	}
}

int main()
{
	int i, j, k, T;

	for (scanf("%d", &T); T-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		assert(1 <= n && n < 125 && 1 <= m && m < 125);

		memset(map, 0, sizeof(map));

		for (i = 1; i <= n; i++)
			for (j = 1; j <= m; j++) {
				scanf("%d", &map[i][j]);
				assert(map[i][j] >= 1);
			}

		sol = m+1;
		for (i = 1, k = 0; i <= m; i++)
			if (map[1][i] == 1) {
				go(1, i, 1);
				if (sol <= m) break;
			}	

		printf("1 %d\n%d %d\n", i, n, sol);

		if (T > 0) printf("\n");
	}

	return 0;
}
