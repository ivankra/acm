#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

// NEWS
int DX[4] = { 0, 1, -1, 0 };
int DY[4] = { -1, 0, 0, 1 };

char maze[80][80];
int width, height;
int visited[80][80][4];

/*
  123456
1 \//\\/
2 \///\/
3 //\\/\
4 \/\///
*/

int visit(int y0, int x0, int d0)
{
	int y = y0, x = x0, d = d0;
	int len = 0;

	for (;;) {
		if (visited[y][x][d]) {
			if (y == y0 && x == x0 && d == d0) return len;
			return -1;
		}

		visited[y][x][d] = 1;
		if (maze[y][x] == '/') {
			d ^= 1;
		} else if (maze[y][x] == '\\') {
			d ^= 2;
		} else {
			return -1;
		}

		y += DY[d];
		x += DX[d];

		len++;
	}
}

int main()
{
	for (int cs = 1; scanf("%d %d", &width, &height) == 2 && width > 0; cs++) {
		memset(maze, 0, sizeof(maze));
		for (int i = 1; i <= height; i++)
			for (int j = 1; j <= width; j++)
				scanf(" %c", &maze[i][j]);

		int ncycles = 0, longestCycle = 0;

		memset(visited, 0, sizeof(visited));
		for (int y0 = 1; y0 <= height; y0++) {
			for (int x0 = 1; x0 <= width; x0++) {
				for (int d0 = 0; d0 < 4; d0++) {
					int c = visit(y0, x0, d0);
					if (c > 0) {
						ncycles++;
						longestCycle = max(longestCycle, c);
					}
				}
			}
		}

		printf("Maze #%d:\n", cs);
		if (ncycles == 0)
			printf("There are no cycles.\n");
		else
			printf("%d Cycles; the longest has length %d.\n", ncycles/2, longestCycle);
		printf("\n");
	}
}
