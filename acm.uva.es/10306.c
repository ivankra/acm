#include <stdio.h>

int cx[128], cy[128], m, s, s2;
int dist[301][301];

int solve()
{
	static int queue[92000], qh, qt;
	int x, y, i, j;

	if (s == 0)
		return 0;

	for (i = 0; i <= s; i++)
		for (j = 0; j <= s; j++)
			dist[i][j] = 0;

	queue[0] = 0;
	dist[0][0] = 0;
	qh = 0;
	qt = 1;

	while (qh < qt) {
		x = (queue[qh] >> 9);
		y = (queue[qh++] & 0x1FF);

		for (i = 0; i < m; i++) {
			j = (x + cx[i]) * (x + cx[i]) + (y + cy[i]) * (y + cy[i]);

			if (j > s2 || dist[x + cx[i]][y + cy[i]] > 0)
				continue;

			if (j == s2)
				return (dist[x][y] + 1);

			dist[x + cx[i]][y + cy[i]] = dist[x][y] + 1;
			queue[qt++] = ((x + cx[i]) << 9) | (y + cy[i]);
		}
	}

	return -1;
}

int main()
{
	int i, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &m, &s) == 2;) {
		s2 = s * s;

		for (i = 0; i < m; i++)
			scanf("%d %d", &cx[i], &cy[i]);

		i = solve();

		printf((i < 0) ? "not possible\n" : "%d\n", i);
	}

	return 0;
}
