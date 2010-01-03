#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

#define INF 0x3fffffff

int width, height;
int cell[1024], N, P, Q;

bool conn_buf[1001][11][21];
#define conn(xy, dx, dy) conn_buf[xy][dx][(dy)+10]

int memo[1001][11][21];

int f(int x, int y, int dx, int dy) {
	int xy = y * width + x;
	int &res = memo[xy][dx][dy+10];
	if (res != -1) return res;
	if (xy == N-1) return res = 0;

	res = INF;

	for (int dx1 = dx-1; dx1 <= dx+1; dx1++) {
		if (dx1 < 0 || dx1 > P) continue;
		for (int dy1 = dy-1; dy1 <= dy+1; dy1++) {
			if (dy1 < -Q || dy1 > Q) continue;
			if (dx1 == 0 && dy1 <= 0) continue;
			if (!conn(xy, dx1, dy1)) continue;
			if (x + dx1 >= width) continue;
			if (y + dy1 < 0 || y + dy1 >= height) continue;

			res <?= 1 + f(x+dx1, y+dy1, dx1, dy1);
		}
	}

	return res;
}

void rec(int x, int y, int dx, int dy) {
	for (;;) {
		assert(f(x, y, dx, dy) <= N);
		printf("%d %d\n", x+1, y+1);

		int xy = y * width + x;
		if (xy == N-1) break;

		for (int dx1 = dx-1; dx1 <= dx+1; dx1++) {
			if (dx1 < 0 || dx1 > P) continue;
			for (int dy1 = dy-1; dy1 <= dy+1; dy1++) {
				if (dy1 < -Q || dy1 > Q) continue;
				if (dx1 == 0 && dy1 <= 0) continue;
				if (!conn(xy, dx1, dy1)) continue;
				if (x + dx1 >= width) continue;
				if (y + dy1 < 0 || y + dy1 >= height) continue;

				if (f(x, y, dx, dy) == 1 + f(x+dx1, y+dy1, dx1, dy1)) {
					x += dx1;
					y += dy1;
					dx = dx1;
					dy = dy1;
					goto done;
				}
			}
		}
done:;
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		if (cs > 1) printf("\n");

		scanf("%d %d %d %d", &width, &height, &P, &Q);
		N = width * height;
		for (int i = 0; i < N; i++) scanf("%d", &cell[i]);

		for (int dx = 0; dx <= P; dx++) {
			for (int dy = -Q; dy <= Q; dy++) {
				if (dx == 0 && dy == 0) {
					for (int xy = 0; xy < N; xy++) conn(xy, dx, dy) = (cell[xy] == 0);
					continue;
				}

				if (dx == 0 && dy < 0) {
					for (int xy = 0; xy < N; xy++) conn(xy, dx, dy) = false;
					continue;
				}

				for (int x = width-1; x >= 0; x--) {
					for (int y1 = 0; y1 < height; y1++) {
						int y = (dy >= 0 ? height-1-y1 : y1);
						int xy = y * width + x;

						bool &res = conn(xy, dx, dy);
						res = false;
						if (cell[xy] != 0) continue;

						if (dx > 0 && x+1 < width) res |= conn(xy+1, dx-1, dy);
						if (dy > 0 && y+1 < height) res |= conn(xy+width, dx, dy-1);
						if (dy < 0 && y > 0) res |= conn(xy-width, dx, dy+1);
					}
				}
			}
		}

		memset(memo, 0xff, sizeof(memo));

		int res = f(0, 0, 0, 0);
		if (res > N) {
			printf("Impossible\n");
		} else {
			printf("%d\n", res);
			rec(0,0,0,0);
		}
	}
}
