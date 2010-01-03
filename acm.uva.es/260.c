#include <stdio.h>
#include <string.h>

int dx[] = { -1, -1, 0, 0, 1, 1 }, dy[] = { -1, 0, -1, 1, 0, 1 };
int p[65536], a[256][256], n, t;

int find(int x)
{
	int z, y;

	for (z = x; p[z] != z; z = p[z]);

	while (x != z) {
		y = p[x];
		p[x] = z;
		x = y;
	}

	return z;
}

int f(int y, int x)
{
	return find((y - 1) * n + x - 1);
}

int main()
{
	int i, j, k;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		memset(a, 0, sizeof(a));
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n && (k = getchar()) != EOF;)
				if (k == 'b' || k == 'w') a[i][j++] = k;

		for (k = n * n, i = 0; i < k; i++)
			p[i] = i;

		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				if (a[i][j] == 'b')
					for (k = 0; k < 6; k++)
						if (a[i + dy[k]][j + dx[k]] == 'b')
							p[f(i, j)] = p[f(i + dy[k], j + dx[k])];

		for (i = 1, k = 'W'; k == 'W' && i <= n; i++)
			for (j = 1; j <= n; j++)
				if (a[1][i] == 'b' && f(1, i) == f(n, j)) k = 'B';

		printf("%d %c\n", t, k);
	}

	return 0;
}
