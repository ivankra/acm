#include <cstdio>
#include <algorithm>
using namespace std;

struct Point {
	int x, y;
	bool operator <(const Point &p) const { return x<p.x || (x==p.x && y<p.y); }
	bool operator ==(const Point &p) const { return x==p.x && y==p.y; }
};

int cross(const Point &o, const Point &a, const Point &b) {
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}

Point P[100010], H[100010];
int N;

int between(const Point &a, const Point &b, const Point &c) {
//	return fabs(dist(a, b) + dist(b, c) - dist(a, c)) < 1e-6;
	return cross(a, b, c) == 0 &&
	       min(a.x, c.x) <= b.x && b.x <= max(a.x, c.x) &&
	       min(a.y, c.y) <= b.y && b.y <= max(a.y, c.y);
}

int inside(const Point &Q) {
	if (H[0] == Q) return 1;

	if (cross(H[0], H[1], Q) < 0) return 0;
	if (cross(H[N-1], H[0], Q) < 0) return 0;

	int left = 1, right = N-1;
	while (right > left) {
		int mid = (left + right) / 2;
		if (mid == left || mid == right) break;

		int c = cross(H[0], H[mid], Q);
		if (c == 0) return between(H[0], Q, H[mid]);

		if (c > 0)
			left = mid;
		else
			right = mid;
	}

	for (int i = left+1; i <= right; i++) {
		Point &O = H[0];
		Point &L = H[i-1];
		Point &R = H[i];

		if (cross(O,L,Q) >= 0 && cross(L,R,Q) >= 0 && cross(R,O,Q) >= 0)
			return 1;
	}

	return 0;
}

void hull() {
	sort(P, P+N);

	int m = 0;
	for (int i = 0; i < N; i++) {
		while (m >= 2 && cross(H[m-2], H[m-1], P[i]) <= 0) m--;
		H[m++] = P[i];
	}

	int t = m;
	for (int i = N-1; i >= 0; i--) {
		while (m-2 >= t-1 && cross(H[m-2], H[m-1], P[i]) <= 0) m--;
		H[m++] = P[i];
	}
	m--;

	N = m;
}

int main() {
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++)
			scanf("%d %d", &P[i].x, &P[i].y);

		hull();

		int nq;
		Point q;

		scanf("%d", &nq);
		while (nq-- > 0) {
			scanf("%d %d", &q.x, &q.y);
			printf(inside(q) ? "inside\n" : "outside\n");
		}
	}
}
