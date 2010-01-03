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
#include <deque>
using namespace std;
typedef long long LL;
const double PI = 2 * acos(0.0);

typedef pair<int, int> PII;

int DX[] = { 1, -1, 0, 0 }, DY[] = { 0, 0, 1, -1 };
int field[64][64], nrows, ncols;
int inside[64][64];
short memo[64][64][64][64][3];

int f(int ay, int ax, int by, int bx, int flag)
{
	short &res = memo[ay][ax][by][bx][flag];
	if (res != -1) return res;

	res = 0;

	if (flag == 0) {
		res >?= f(ay, ax, by, bx, 1);
		res >?= f(ay, ax, by, bx, 2);
	}

	if ((flag == 0 && field[ay][ax] <= field[by][bx]) || flag == 1) {
		for (int dir = 0; dir < 4; dir++) {
			int ny = ay + DY[dir];
			int nx = ax + DX[dir];
			if (!inside[ny][nx]) continue;
			if (field[ny][nx] <= field[ay][ax]) continue;
			if (ny == by && nx == bx) continue;
			res >?= 1 + f(ny, nx, by, bx, flag);
		}
	}

	if ((flag == 0 && field[by][bx] <= field[ay][ax]) || flag == 2) {
		for (int dir = 0; dir < 4; dir++) {
			int ny = by + DY[dir];
			int nx = bx + DX[dir];
			if (!inside[ny][nx]) continue;
			if (field[ny][nx] <= field[by][bx]) continue;
			if (ny == ay && nx == ax) continue;
			res >?= 1 + f(ay, ax, ny, nx, flag);
		}
	}

	return res;
}

void recover(int ay, int ax, int by, int bx, int flag, deque<PII> &path)
{
	int res = f(ay, ax, by, bx, flag);
	if (res <= 0) return;

	if (flag == 0) {
		if (res == f(ay, ax, by, bx, 1)) {
			recover(ay, ax, by, bx, 1, path);
			return;
		}

		if (res == f(ay, ax, by, bx, 2)) {
			recover(ay, ax, by, bx, 2, path);
			return;
		}
	}

	if ((flag == 0 && field[ay][ax] <= field[by][bx]) || flag == 1) {
		for (int dir = 0; dir < 4; dir++) {
			int ny = ay + DY[dir];
			int nx = ax + DX[dir];
			if (!inside[ny][nx]) continue;
			if (field[ny][nx] <= field[ay][ax]) continue;
			if (ny == by && nx == bx) continue;

			if (res == 1 + f(ny, nx, by, bx, flag)) {
				path.push_front(PII(ny, nx));
				recover(ny, nx, by, bx, flag, path);
				return;
			}
		}
	}

	if ((flag == 0 && field[by][bx] <= field[ay][ax]) || flag == 2) {
		for (int dir = 0; dir < 4; dir++) {
			int ny = by + DY[dir];
			int nx = bx + DX[dir];
			if (!inside[ny][nx]) continue;
			if (field[ny][nx] <= field[by][bx]) continue;
			if (ny == ay && nx == ax) continue;

			if (res == 1 + f(ay, ax, ny, nx, flag)) {
				path.push_back(PII(ny, nx));
				recover(ay, ax, ny, nx, flag, path);
				return;
			}
		}
	}

	assert(false);
}

int main()
{
	scanf("%d %d", &nrows, &ncols);
	memset(inside, 0, sizeof(inside));
	for (int y = 1; y <= nrows; y++) {
		for (int x = 1; x <= ncols; x++) {
			scanf("%d", &field[y][x]);
			inside[y][x] = 1;
		}
	}

	memset(memo, 0xff, sizeof(memo));

	int bestY = 1, bestX = 1, best = 0;
	for (int y = 1; y <= nrows; y++) {
		for (int x = 1; x <= ncols; x++) {
			int len = 1 + f(y, x, y, x, 0);
			if (len > best) {
				best = len;
				bestY = y;
				bestX = x;
			}
		}
	}

	printf("%d\n", best);

	deque<PII> path;
	path.push_back(PII(bestY, bestX));
	recover(bestY, bestX, bestY, bestX, 0, path);

	for (int i = 0; i < (int)path.size(); i++) {
		int y = path[i].first;
		int x = path[i].second;
		printf("%d %d\n", y, x);
//		printf("%d %d: %d\n", y, x, field[y][x]);
	}
	assert((int)path.size() == best);
}
