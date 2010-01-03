#include <stdio.h>
#include <string.h>

#define EWALL	1
#define SWALL	2
#define NWALL	4
#define WWALL	8

int map[16][16], wall[16][16], width, height, x0, y0, x1, y1;

void find()
{
	static int dx[] = { -1, 0, 1, 0 }, dy[] = { 0, -1, 0, 1 };
	static int dw[] = { WWALL, NWALL, EWALL, SWALL };
	static int backy[16][16], backx[16][16], dir[16][16];
	int d, k, m, x, y;

	memset(backx, 0, sizeof(backx));
	memset(backy, 0, sizeof(backy));
	memset(dir, 0, sizeof(dir));

	for (x = x0, y = y0, m = 1; x != x1 || y != y1;) {
		if (dir[y][x] >= 4) {
			map[y][x] = -1;
			k = backy[y][x];
			x = backx[y][x];
			y = k;
			m--;
			continue;
		}

		d = dir[y][x]++;

		if (wall[y][x] & dw[d])
			continue;

		if ((y + dy[d]) < 1 || (y + dy[d]) > height)
			continue;

		if ((x + dx[d]) < 1 || (x + dx[d]) > width)
			continue;

		if (map[y + dy[d]][x + dx[d]] != 0)
			continue;

		map[y][x] = m++;

		backx[y + dy[d]][x + dx[d]] = x;
		backy[y + dy[d]][x + dx[d]] = y;

		y += dy[d];
		x += dx[d];

		dir[y][x] = 0;
	}

	map[y1][x1] = m;
}

void print()
{
	int r, c;

	for (r = 1; r <= height; r++) {
		for (c = 1; c <= width; c++)
			printf((wall[r][c] & NWALL) ? "+---" : "+   ");
		printf("+\n");

		for (c = 1; c <= width; c++) {
			printf((wall[r][c] & WWALL) ? "|" : " ");
			if (map[r][c] < 0)
				printf("???");
			else if (map[r][c] == 0)
				printf("   ");
			else
				printf("%3d", map[r][c]);
		}
		printf("|\n");
	}

	for (c = 1; c <= width; c++)
		printf("+---");
	printf("+\n");
}


int main()
{
	int i, j, m, t;

	for (t = 1; scanf("%d%d%d%d%d%d", &height, &width, &y0, &x0, &y1, &x1) == 6; t++) {
		if (width == 0 || height == 0) break;

		memset(map, 0, sizeof(map));
		memset(wall, 0, sizeof(wall));

		for (i = 1; i <= height; i++) {
			for (j = 1; j <= width && scanf("%d", &m) == 1; j++)  {
				wall[i][j] |= m;
				if (m & EWALL) wall[i][j + 1] |= WWALL;
				if (m & SWALL) wall[i + 1][j] |= NWALL;
			}
		}

		for (i = 1; i <= height; i++) {
			wall[i][1] |= WWALL;
			wall[i][width] |= EWALL;
		}

		for (i = 1; i <= width; i++) {
			wall[1][i] |= NWALL;
			wall[height][i] |= SWALL;
		}

		find();

		printf("Maze %d\n\n", t);
		print();
		if (t > 0) printf("\n\n");
	}

	return 0;
}
