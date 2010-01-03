#include <cstdio>
#include <algorithm>
using namespace std;

struct Point {
	long long x, y;
	Point(long long x_ = 0, long long y_ = 0) : x(x_), y(y_) {}
	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

int cross(Point o, Point a, Point b) {
	long long t = (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
	return t == 0 ? 0 : (t > 0 ? 1 : -1);
}

struct Segment {
	Point A, B;
	long long a, b, c;

	Segment() {}

	Segment(Point A_, Point B_) : A(A_), B(B_) {
		a = B.y - A.y;
		b = A.x - B.x;
		c = a * A.x + b * A.y;
	}

	bool intersects(const Segment &other) {
		if (cross(other.A, other.B, A) * cross(other.A, other.B, B) > 0)
			return false;

		if (cross(A, B, other.A) * cross(A, B, other.B) > 0)
			return false;

		if (cross(other.A, A, B) == 0 && cross(other.B, A, B) == 0)
			// parallel or overlapping segments
			return false;

		return true;
	}

	bool contains(Point P) const {
		if (cross(A, B, P) != 0) return false;
		if (P.x < min(A.x, B.x)) return false;
		if (P.x > max(A.x, B.x)) return false;
		if (P.y < min(A.y, B.y)) return false;
		if (P.y > max(A.y, B.y)) return false;
		return true;
	}

	bool overlaps(const Segment &other) {
		if (cross(A, other.A, other.B) != 0) return false;
		if (cross(B, other.A, other.B) != 0) return false;

		if (contains(other.A) || contains(other.B)) return true;
		if (other.contains(A) || other.contains(B)) return true;

		return false;
	}

	Segment uniteWith(const Segment &other) {
		Point P[4] = { A, B, other.A, other.B };
		sort(P, P+4);
		return Segment(P[0], P[3]);
	}
};

// Do the three pairwise-intersecting segments intersect at the same point?
bool concurrent(const Segment &S1, const Segment &S2, const Segment &S3) {
	long long d = S1.a * S2.b - S2.a * S1.b;
	long long x = S1.c * S2.b - S2.c * S1.b;
	long long y = S1.a * S2.c - S2.a * S1.c;
	if (d < 0) { x = -x; y = -y; d = -d; }
	return S3.a * x + S3.b * y == S3.c * d;  // 4*m^4
}

Segment seg[1000];
int N;

int solve() {
	// Unite overlapping segments
	while (true) {
		bool changed = false;
		for (int i = 0; i < N; i++) {
			for (int j = i+1; j < N; j++) {
				if (seg[i].overlaps(seg[j])) {
					seg[i] = seg[i].uniteWith(seg[j]);
					seg[j] = seg[N-1];
					N--;
					changed = true;
				}
			}
		}
		if (!changed) break;
	}

	// Counting
	int res = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i+1; j < N; j++) {
			if (!seg[j].intersects(seg[i])) continue;
			for (int k = j+1; k < N; k++) {
				if (!seg[k].intersects(seg[i])) continue;
				if (!seg[k].intersects(seg[j])) continue;
				if (concurrent(seg[i], seg[j], seg[k])) continue;
				res++;
			}
		}
	}

	return res;
}

int main()
{
	while (scanf("%d", &N) == 1 && N > 0) {
		for (int i = 0; i < N; i++) {
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			seg[i] = Segment(Point(x1, y1), Point(x2, y2));
		}
		printf("%d\n", solve());
	}
	return 0;
}
