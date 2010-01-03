#include <stdio.h>
#include <string.h>

static char a[128][128];
static int st[16384], m, n;

static void dfs(int y, int x)
{
	int t;

	t = 0;
	st[t++] = y;
	st[t++] = x;
	a[y][x] = 0;

	while (t > 1) {
		x = st[--t];
		y = st[--t];

#define GO(Y,X) if (a[Y][X] == '@') { a[Y][X]=0; st[t++]=(Y); st[t++]=(X); }
		GO(y - 1, x - 1);
		GO(y - 1, x);
		GO(y - 1, x + 1);
		GO(y, x - 1);
		GO(y, x + 1);
		GO(y + 1, x - 1);
		GO(y + 1, x);
		GO(y + 1, x + 1);
	}
}

int main()
{
	int i, j, k;

	while (scanf("%d %d", &m, &n) == 2 && m > 0) {
		memset(a, '\0', sizeof(a[0]) * (m + 2));

		for (i = 1; i <= m; i++)
			scanf(" %[*@]", a[i] + 1);

		for (i = 1, k = 0; i <= m; i++)
			for (j = 1; j <= n; j++)
				if (a[i][j] == '@') {
					dfs(i, j);
					k++;
				}

		printf("%d\n", k);
	}

	return 0;
}
