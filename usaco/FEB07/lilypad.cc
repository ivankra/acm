/*
TASK: lilypad
ID: infnty1
LANG: C++
*/
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

const int INF = 1<<30;

int field[32][32], width, height, startY, startX, destY, destX;
bool adj[32][32][32][32];

int minAdd[32][32];
long long ways[32][32];

void adj_dfs(bool a[32][32], int y, int x) {
	if (a[y][x]) return;
	a[y][x] = true;

	for (int dx = -2; dx <= 2; dx++) {
		for (int dy = -2; dy <= 2; dy++) {
			if ((abs(dx) == 1 && abs(dy) == 2) ||
			    (abs(dx) == 2 && abs(dy) == 1)) {
				int y1 = y + dy;
				int x1 = x + dx;
				if (y1 < 1 || y1 > height || x1 < 1 || x1 > width)
					continue;

				if (field[y1][x1] == 2)
					continue;

				if (field[y1][x1] == 1)
					adj_dfs(a, y1, x1);
				a[y1][x1] = true;
			}
		}
	}
}

int main()
{
	freopen("lilypad.in", "r", stdin);
	freopen("lilypad.out", "w", stdout);

	scanf("%d %d", &height, &width);
	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width; j++) {
			scanf(" %d", &field[i][j]);
			if (field[i][j] == 3) {
				startY = i;
				startX = j;
				field[i][j] = 1;
			} else if (field[i][j] == 4) {
				destY = i;
				destX = j;
				field[i][j] = 1;
			}
		}
	}

	memset(adj, 0, sizeof(adj));
	for (int i = 1; i <= height; i++)
		for (int j = 1; j <= width; j++)
			adj_dfs(adj[i][j], i, j);

	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width; j++) {
			minAdd[i][j] = INF;
			ways[i][j] = 0;
		}
	}
	minAdd[startY][startX] = 0;
	ways[startY][startX] = 1;

	queue<int> Q;
	Q.push(startY);
	Q.push(startX);

	int destAdd = -1;
	long long destWays = 0;

	while (!Q.empty()) {
		int y0 = Q.front(); Q.pop();
		int x0 = Q.front(); Q.pop();

		//printf("y=%d x=%d: minAdd=%d ways=%d\n", y0, x0, minAdd[y0][x0], (int)ways[y0][x0]);

		if (adj[y0][x0][destY][destX]) {
			//printf("  destination reachable\n");
			destAdd = minAdd[y0][x0];
			destWays += ways[y0][x0];
			continue;
		}

		for (int y1 = 1; y1 <= height; y1++) {
			for (int x1 = 1; x1 <= width; x1++) {
				if (!adj[y0][x0][y1][x1]) continue;
				if (field[y1][x1] != 0) continue;

				if (minAdd[y0][x0] + 1 < minAdd[y1][x1]) {
					minAdd[y1][x1] = minAdd[y0][x0] + 1;
					ways[y1][x1] = ways[y0][x0];
					Q.push(y1);
					Q.push(x1);
				} else if (minAdd[y0][x0] + 1 == minAdd[y1][x1]) {
					ways[y1][x1] += ways[y0][x0];
				}
			}
		}
	}

	printf("%d\n", destAdd);
	if (destAdd >= 0)
		printf("%lld\n", destWays);
}
