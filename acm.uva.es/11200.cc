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

int dx[] = { 0, -1, 1, 0 }, dy[] = { -1, 0, 0, 1 };	// NWES

char maze[512][512];
int width, height;

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &width, &height);

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				for (;;) {
					int c = getchar();
					if (c == '/' || c == '\\') {
						maze[i][j] = c;
						break;
					}
				}
			}
		}

		int res = 0;
		for (int x0 = 0; x0 < width; x0++) {
			for (int x = x0, y = 0, dir = 3;;) {
				if (x < 0 || x >= width || y < 0 || y >= height)
					break;

				dir ^= (maze[y][x] == '/' ? 2 : 1);
				y += dy[dir];
				x += dx[dir];

				if  (y == height) {
					res++;
					break;
				}
			}
		}

		printf("%d\n", res);
	}
}
