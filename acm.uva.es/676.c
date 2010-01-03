#include <stdio.h>
#include <string.h>

int main()
{
	static int dx[] = { 0, 1, 1, -1, -1 }, dy[] = { 0, -1, 1, 1, -1 };
	static int m[16][16], py[16][16], px[16][16], rx[65536], ry[65536];
	static int x1, y1, x2, y2, t, p, n;
	int i, j, x, y;

	for (scanf("%d", &p), t = 0; t < p; t++) {
		if (t != 0)
			printf("\n");

		scanf(" ( %d , %d) ( %d , %d )", &y1, &x1, &y2, &x2);

		if (((x1 + y1) & 1) != ((x2 + y2) & 1)) {
			printf("fail\n");
			continue;
		}

		memset(m, 0, sizeof(m));
		memset(px, 0, sizeof(px));
		memset(py, 0, sizeof(py));

		for (x = x1, y = y1, n = 0; n <= 50000;) {
			if (x == x2 && y == y2)
				break;

			while (++m[y][x] < 5) {
				i = x + dx[m[y][x]];
				j = y + dy[m[y][x]];

				if (i <= 0 || j <= 0 || i >= 10 || j >= 10)
					continue;

				if (m[j][i] != 0)
					continue;

				rx[n] = i;
				ry[n] = j;
				n++;

				px[j][i] = x;
				py[j][i] = y;

				x = i;
				y = j;
				break;
			}

			if (m[y][x] == 5) {
				m[y][x] = 0;

				i = px[y][x];
				j = py[y][x];

				px[y][x] = py[y][x] = 0;

				rx[n] = x = i;
				ry[n] = y = j;
				n++;

				if (x == 0 || y == 0) break;
				continue;
			}
		}

		if (x == x2 && y == y2) {
			printf("(%d,%d)", y1, x1);
			for (i = 0; i < n; i++)
				printf(", (%d,%d)", ry[i], rx[i]);
			printf("\n");
			continue;
		}

		if (n > 50000) {
			printf("more than 50000 steps\n");
			continue;
		}

		printf("fail\n");
	}

	return 0;
}
