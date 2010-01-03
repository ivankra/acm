#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int dy[]={-1,0,1,0}, dx[] = {0,1,0,-1};
int a[64][64], u[64][64], m, n, count;

void go(int y, int x, int d)
{
	if (y < 0 || x < 0 || y >= m || x >= n || u[y][x]) return;
	if (y == m-1 && x == n-1) { count++; return; }
	if (a[y][x] == 0) return;

	u[y][x] = 1;
	if (a[y][x] == 1) {
		go(y+dy[d], x+dx[d], d);
	} else {
		go(y+dy[(d+1)&3], x+dx[(d+1)&3], (d+1)&3);
		go(y+dy[(d+3)&3], x+dx[(d+3)&3], (d+3)&3);
	}
	u[y][x] = 0;
}

int main()
{
	int i, j, k, c, t, s;

	scanf("%d", &t);
	while (t-- > 0) {
		i = scanf("%d %d", &m, &n);
		assert(i == 2 && 1 <= m && 1 <= n && m*n <= 64);

		memset(a, 0, sizeof(a));
		for (i = 0; i < m; i++) {
			for (s = 0; s < 3; s++) {
				while ((c = getchar()) != EOF && c != '|');
				for (j = 0; j < n; j++) {
					for (k = 0; (c = getchar()) != EOF && c != '|';)
						if (c == '*') k++;
					if (k == 3 || a[i][j] < 0) a[i][j] = -1;
					else if (k == 1) a[i][j]++;
				}
			}
			for (j = 0; j < n; j++)
				if (a[i][j] == 0) a[i][j] = 0;
				else if (a[i][j] == 1) a[i][j] = 2;
				else a[i][j] = 1;
		}

		while ((c = getchar()) != EOF && !isdigit(c));
		if (c != EOF) ungetc(c, stdin);

		if (n == 1 && m == 1) {
			count = 1;
		} else {
			count = 0;
			memset(u, 0, sizeof(u));
			go(0,0,1);
			go(0,0,2);
		}

		printf("Number of solutions: %d\n", count);
	}

	return 0;
}
