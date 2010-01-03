#include <cmath>
#include <cctype>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int height[32][32], nrows, ncols;
bool canMove[32*32][4];
int dx[]={1,-1,0,0}, dy[]={0,0,1,-1};

bool isvalid(int y, int x) {
	return 0 <= y && y < nrows && 0 <= x && x < ncols;
}

int sqr(int x) { return x*x; }

bool travelOkay(int y1, int x1, int y2, int x2) {
	return abs(height[y1][x1] - height[y2][x2]) <= 10;
//	return sqr(height[y1][x1] - height[y2][x2]) + 1 <= 100;
}

bool solve(int s, int t) {
	double dist[32*32];
	bool seen[32*32];
	int prev[32*32];

	int N = nrows*ncols;
	for (int i = 0; i < N; i++) {
		seen[i] = false;
		prev[i] = -1;
	}

	dist[s] = 0;
	prev[s] = s;

	for (;;) {
		int u = -1;
		for (int i = 0; i < N; i++)
			if (prev[i] >= 0 && !seen[i] && (u < 0 || dist[i] < dist[u])) u = i;
		if (u < 0) break;

		int y1 = u / ncols;
		int x1 = u % ncols;
		seen[u] = true;

		if (u == t) break;

		for (int d = 0; d < 4; d++) {
			if (!canMove[u][d]) continue;

			int y2 = y1 + dy[d];
			int x2 = x1 + dx[d];
			int v = y2 * ncols + x2;
			if (seen[v]) continue;

			//double cost = sqrt(sqr(height[y1][x1] - height[y2][x2]) + 1.0);
			double cost = 1.0;

			if (prev[v] < 0 || dist[u] + cost < dist[v]) {
				dist[v] = dist[u] + cost;
				prev[v] = u;
			}
		}
	}

	if (prev[t] < 0) return false;

	vector<int> path;
	for (int i = t;; i = prev[i]) {
		path.push_back(i);
		if (i == s) break;
	}

	for (int i = path.size()-1; i >= 0; i--) {
		int u = path[i];
		printf("%d-%d%s", u/ncols+1, u%ncols+1, i==0 ? "\n" : " to ");
	}

	return true;
}

int main()
{
	int query = 0;
	while (scanf("%d %d", &nrows, &ncols) == 2) {
		for (int i = 0; i < nrows; i++)
			for (int j = 0; j < ncols; j++)
				assert(scanf("%d", &height[i][j]) == 1);

		for (int y = 0; y < nrows; y++)
			for (int x = 0; x < ncols; x++)
				for (int d = 0; d < 4; d++)
					canMove[y*ncols+x][d] = false;

		for (;;) {
			int y1, x1, y2, x2;
			assert(scanf("%d %d %d %d", &y1, &x1, &y2, &x2) == 4);
			if (y1-- == 0 || x1-- == 0 || y2-- == 0 || x2-- == 0) break;
			assert(isvalid(y1, x1) && isvalid(y2, x2));

			int d;
			for (d = 0; d < 4; d++) {
				int t = abs(y1 - y2) + abs(x2 - x1);
				if (y1 + t*dy[d] == y2 && x1 + t*dx[d] == x2) break;
			}
			assert(0 <= d && d < 4);

			while (y1 != y2 || x1 != x2) {
				if (travelOkay(y1, x1, y1+dy[d], x1+dx[d]))
					canMove[y1*ncols+x1][d] = true;
				y1 += dy[d]; x1 += dx[d];
			}
		}

		for (;;) {
			int y1, x1, y2, x2;
			assert(scanf("%d %d %d %d", &y1, &x1, &y2, &x2) == 4);
			if (y1-- == 0 || x1-- == 0 || y2-- == 0 || x2-- == 0) break;
			assert(isvalid(y1, x1) && isvalid(y2, x2));

			if (query++ > 0) printf("\n");

			if (y1 == y2 && x1 == x2)
				printf("To get from %d-%d to %d-%d, stay put!\n", y1+1, x1+1, y2+1, x2+1);
			else if (!solve(y1*ncols+x1, y2*ncols+x2))
				printf("There is no acceptable route from %d-%d to %d-%d.\n", y1+1, x1+1, y2+1, x2+1);
		}
	}
}
