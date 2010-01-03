#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

struct Point {
	int x, y;
	bool operator <(const Point &p) const { return y < p.y; }
} P[200];
int N;

vector<Point> sweep[11000];

int Floor(int p, int q) {
	if (q < 0) { p = -p; q = -q; }
	return p >= 0 ? (p / q) : -((-p + q - 1) / q);
}

int Ceil(int p, int q) {
	if (q < 0) { p = -p; q = -q; }
	return p >= 0 ? ((p+q-1)/q) : -((-p) / q);
}

int lineCeil(const Point &A, const Point &B, int x) {
	return A.y + Ceil((B.y-A.y)*(x-A.x), B.x-A.x);
}

int lineFloor(const Point &A, const Point &B, int x) {
	return A.y + Floor((B.y-A.y)*(x-A.x), B.x-A.x);
}

int main() {
	while (scanf("%d", &N) == 1 && N > 0) {
		for (int i = 0; i < N; i++)
			scanf("%d %d", &P[i].x, &P[i].y);
		P[N] = P[0];

		for (int i = 0; i < 11000; i++) sweep[i].clear();

		for (int i = 0; i < N; i++) {
			Point A = P[i], B = P[i+1];
			if (A.x == B.x) continue;
			if (A.x > B.x) swap(A, B);

			for (int x = A.x; x < B.x; x++) {
				Point e;
				e.x = -1;
				e.y = max(lineCeil(A, B, x), lineCeil(A, B, x+1));
				sweep[x].push_back(e);

				e.x = +1;
				e.y = min(lineFloor(A, B, x), lineFloor(A, B, x+1));
				sweep[x].push_back(e);

//printf("A=%d,%d  B=%d,%d  at x=%d: y=%d..%d\n",A.x,A.y,B.x,B.y, x,lineFloor(A,B,x),lineCeil(A,B,x));
			}
		}

		int ans[2] = { 0, 0 };

		for (int x = 0; x < 10100; x++) {
			vector<Point> &s = sweep[x];
			if (s.size() == 0) continue;

			sort(s.begin(), s.end());

//			printf("x=%d..%d:\n", x, x+1);

			int y0 = 0, lc = 0, ic = 0, m = s.size();
			for (int i = 0; i < m;) {
//				printf("  at y=%d: %+d%s\n", s[i].y, s[i].x, s[i].y==y0 ? "" : " *");
				if (s[i].y == y0) {
					lc += s[i].x;
					if (s[i].x == -1) ic++;
					i++;
					continue;
				}

				int y1 = s[i].y;
				if (lc == 0 && ic%2 == 1) {
					int col = (x + y0) % 2;
					int n = y1 - y0;
//					printf("    col=%d n=%d\n", col, n);
					if (n % 2 == 1) {
						ans[col]++;
						col ^= 1;
						n--;
					}
					ans[0] += n/2;
					ans[1] += n/2;
				}

				y0 = y1;
			}
		}

		if (ans[0] < ans[1]) swap(ans[0], ans[1]);
		printf("%d %d\n", ans[0], ans[1]);
	}
}
