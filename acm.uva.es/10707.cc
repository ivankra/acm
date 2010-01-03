#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
typedef vector<int> VI;
typedef vector<VI> VVI;

int cell[128][128];
VI cur_group;

int encode(int y, int x) { return ((y+1000) << 16) + x+1000; }
void decode(int i, int &y, int &x) {
	x = (i & 65535) - 1000;
	y = (i >> 16) - 1000;
}

void dfs(int y, int x) {
	if (cell[y][x] != 0) {
		cell[y][x] = 0;
		cur_group.push_back(encode(y, x));
		dfs(y-1, x);
		dfs(y+1, x);
		dfs(y, x-1);
		dfs(y, x+1);
	}
}

void normalize(VI &group)
{
	int n = group.size(), x, y;
	VI g = group;
	group[0] = 1000000000;
	for (int yflip = 0; yflip < 2; yflip++) {
		for (int xflip = 0; xflip < 2; xflip++) {
			for (int r = 0; r < 4; r++) {
				int min_x = 1000000000, min_y = 1000000000;
				for (int i = 0; i < n; i++) {
					decode(g[i], x, y);
					min_x <?= x;
					min_y <?= y;
				}

				for (int i = 0; i < n; i++) {
					decode(g[i], x, y);
					g[i] = encode(x - min_x, y - min_y);
				}

				sort(g.begin(), g.end());

				if (g < group)
					group = g;

				for (int i = 0; i < n; i++) {
					decode(g[i], x, y);
					g[i] = encode(y, -x);
				}
			}

			for (int i = 0; i < n; i++) {
				decode(g[i], x, y);
				g[i] = encode(-x, y);
			}
		}

		for (int i = 0; i < n; i++) {
			decode(g[i], x, y);
			g[i] = encode(x, -y);
		}
	}
}

int width, height, N;

void readBoard(VVI &board)
{
	int i, x, y;

	memset(cell, 0, sizeof(cell));
	for (i = 0; i < N; i++) {
		scanf("%d %d", &x, &y);
		cell[y+1][x+1] = 1;
	}

	board.clear();
	for (y = 1; y <= height; y++) {
		for (x = 1; x <= width; x++) {
			if (cell[y][x] != 0) {
				cur_group.clear();
				dfs(y, x);
				normalize(cur_group);
				board.push_back(cur_group);
			}
		}
	}
	sort(board.begin(), board.end());
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		VVI a, b;
		scanf("%d %d %d", &width, &height, &N);
		readBoard(a);
		readBoard(b);
		printf(a == b ? "YES\n" : "NO\n");
	}
}
