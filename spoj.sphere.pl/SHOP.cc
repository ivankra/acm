#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int cost(char c) { return isdigit(c) ? c-'0' : 0; }

int main()
{
	char maze[32][32];
	int dist[32][32], seen[32][32], height, width;

	while (scanf("%d %d", &width, &height) == 2 && height > 0) {
		memset(maze, 'X', sizeof(maze));
		memset(dist, 0x3f, sizeof(dist));
		memset(seen, 0, sizeof(seen));
		for (int i = 1; i <= height; i++) {
			for (int j = 1; j <= width; j++) {
				scanf(" %c", &maze[i][j]);
				if (maze[i][j] == 'S') dist[i][j] = 0;
			}
		}

		for (;;) {
			int uy = -1, ux = -1;
			for (int i = 1; i <= height; i++) {
				for (int j = 1; j <= width; j++) {
					if (maze[i][j] == 'X') continue;
					if (!seen[i][j] && (uy < 0 || dist[i][j] < dist[uy][ux]))
						uy = i, ux = j;
				}
			}

			if (maze[uy][ux] == 'D') {
				printf("%d\n", dist[uy][ux]);
				break;
			}

			seen[uy][ux] = 1;
			for (int dir = 0; dir < 4; dir++) {
				int y = uy + "0211"[dir] - '1';
				int x = ux + "1102"[dir] - '1';
				if (maze[y][x] == 'X') continue;
				if (dist[uy][ux] + cost(maze[uy][ux]) < dist[y][x]) {
					dist[y][x] = dist[uy][ux] + cost(maze[uy][ux]);
				}
			}
		}
	}
}
