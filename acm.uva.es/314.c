#include <stdio.h>
#include <string.h>

int a[64][64], m, n, srcy, srcx, srcd, desty, destx;

int check(int y, int x)
{
	return ((y >= 1) && (y <= m) && (x >= 1 && x <= n) &&
		(a[y][x] | a[y+1][x] | a[y][x+1] | a[y+1][x+1]) == 0);
}

int solve()
{
	static int dy[4] = { -1, 0, 1, 0 }, dx[4] = { 0, -1, 0, 1 };
	static int d[16384], q[16384], h, t;
	int i, k, s, sy, sx, sd;

	memset(d, 0, sizeof(d));

	h = t = 0;
	d[q[t++] = srcy * 256 + srcx * 4 + srcd] = 1;

	while (h < t) {
		s = q[h++];
		sy = s >> 8;
		sx = (s >> 2) & 0x3F;
		sd = s & 3;

		if (sy == desty && sx == destx)
			return (d[s] - 1);

		for (i = 1; i <= 3; i += 2) {
			k = (s & ~3) | ((sd + i) & 3);
			if (d[k] == 0) {
				d[k] = d[s] + 1;
				q[t++] = k;
			}
		}

		for (i = 1; i <= 3; i++) {
			sy += dy[sd];
			sx += dx[sd];

			if (!check(sy, sx))
				break;

			k = (sy << 8) | (sx << 2) | sd;
			if (d[k] == 0) {
				d[k] = d[s] + 1;
				q[t++] = k;
			}
		}
	}

	return -1;
}

int main()
{
	static char s[1024];
	int i, j;

	while (scanf("%d %d", &m, &n) == 2 && (m > 0 || n > 0)) {
		for (i = 0; i <= (m + 3); i++)
			for (j = 0; j <= (n + 3); j++)
				a[i][j] = 1;

		for (i = 1; i <= m; i++)
			for (j = 1; j <= n; j++)
				scanf("%d", &a[i][j]);

		scanf("%d %d %d %d %s", &srcy, &srcx, &desty, &destx, s);

		if (s[0] == 'w' || s[0] == 'W')
			srcd = 1;
		else if (s[0] == 's' || s[0] == 'S')
			srcd = 2;
		else if (s[0] == 'e' || s[0] == 'E')
			srcd = 3;
		else
			srcd = 0;

		printf("%d\n", solve());
	}

	return 0;
}
