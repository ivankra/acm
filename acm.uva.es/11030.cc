#include <algorithm>
#include <vector>
#include <cstdio>
#include <cassert>
using namespace std;

struct Point {
	int x, y;
};

// Finds winding number of Q around point P.
// Returns -1 if P lies on the boundary of polygon Q
int winding_number(const Point &P, const vector<Point> &Q) {
	int w = 0, n = Q.size();
	for (int i = 0; i < n; i++) {
		const Point &A = Q[i], &B = Q[(i+1)<n?i+1:0];
		if (A.x == P.x && A.y == P.y) return -1;
		if (A.x == B.x && A.y == B.y) continue;

		if (A.y == P.y && B.y == P.y) {
			if (min(A.x, B.x) <= P.x && P.x <= max(A.x, B.x)) return -1;
			continue;
		}

		if (A.y <= P.y && B.y <= P.y) continue;
		if (A.y > P.y && B.y > P.y) continue;

		long long det = (A.x-P.x)*(B.y-P.y)-(A.y-P.y)*(B.x-P.x);
		if (det == 0) return -1;
		w += (det < 0) ? -1 : 1;
	}
	assert((abs(w) & 1) == 0);
	return w/2;
}

int inside(const Point &P, const vector<Point> &poly) {
	return winding_number(P, poly) != 0 ? 1 : 0;
}

int main() {
	int T, n;
	vector<Point> P[16];

	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		printf("Case %d:\n", cs);

		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			int m; scanf("%d", &m);
			P[i].resize(m);
			for (int j = 0; j < m; j++)
				scanf("%d %d", &P[i][j].x, &P[i][j].y);
		}

		int nq;
		for (scanf("%d", &nq); nq-- > 0;) {
			Point A, B;
			scanf("%d %d %d %d", &A.x, &A.y, &B.x, &B.y);

			int res = 0;
			for (int i = 0; i < n; i++)
				res += inside(A, P[i]) ^ inside(B, P[i]);
			printf("%d\n", res);
		}
	}
}
