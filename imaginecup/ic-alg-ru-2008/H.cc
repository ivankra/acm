#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
using namespace std;
#define SIZE(x) int((x).size())
#define FOREACH(it, x) for(__typeof((x).begin())it=(x).begin();it!=(x).end();++it)
typedef long long LL;
typedef vector<int> VI;

template<typename T>
struct Rational {
	typedef Rational<T> R;
	T p, q;
	Rational() { p = 0; q = 1; }
	Rational(T pp, T qq) : p(pp), q(qq) { reduce(); }
	void reduce() {
		if (q < 0) { p = -p; q = -q; }
		T g = __gcd(p < 0 ? -p : p, q); p /= g; q /= g;
	}
	bool operator ==(const R &b) const { return p == b.p && q == b.q; }
	// ordered pair comparison
	bool operator <(const R &b) const { return p < b.p || (p == b.p && q < b.q); }
};
typedef Rational<long long> Frac;

bool good(Frac x, LL upper) {
	return 0 <= x.p && x.p <= upper * x.q;
}

struct Line {
	LL a, b, c;  //ax+by=c
	LL x1, y1, x2, y2;
	Line() {}
	Line(LL _x1, LL _y1, LL _x2, LL _y2) {
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;

		a = y2 - y1;
		b = x1 - x2;
		c = a * x1 + b * y1;
	}

	bool contains(LL x, LL y) const {
		return a*x + b*y == c;
	}
};

bool same(const Line &l, const Line &m) {
	return m.contains(l.x1, l.y1) && m.contains(l.x2, l.y2);
}

int main()
{
	int W, H, N, bad[200];
	Line line[200];

	cin >> W >> H >> N;

	line[0] = Line(0,0, W,0);
	line[1] = Line(W,0, W,H);
	line[2] = Line(W,H, 0,H);
	line[3] = Line(0,H, 0,0);

	memset(bad, 0, sizeof(bad));

	for (int i = 4; i < 4+N; i++) {
		LL x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		line[i] = Line(x1, y1, x2, y2);

		Line l = line[i];
		bad[i] |= l.contains(0,0) && l.contains(W,0);
		bad[i] |= l.contains(W,0) && l.contains(W,H);
		bad[i] |= l.contains(W,H) && l.contains(0,H);
		bad[i] |= l.contains(0,H) && l.contains(0,0);
		bad[i] |= (x1 == x2 && y1 == y2);

		if (!bad[i]) {
			for (int j = 0; j < i; j++) {
				if (!bad[j] && same(line[i], line[j])) {
					bad[i] = 1;
					break;
				}
			}
		}
	}

	int res = 1;
	for (int i = 4; i < 4+N; i++) {
		if (bad[i]) continue;

		set< pair<Frac, Frac> > ss;

		for (int j = 0; j < i; j++) {
			if (bad[j]) continue;

			const Line &l = line[i];
			const Line &m = line[j];

			// l.a x + l.b y = l.c
			// m.a x + m.b y = m.c

			LL det = l.a*m.b - m.a*l.b;
			if (det == 0) continue;

			Frac xx(l.c*m.b - m.c*l.b, det);
			Frac yy(l.a*m.c - m.a*l.c, det);

			if (!good(xx, W)) continue;
			if (!good(yy, H)) continue;

			pair<Frac, Frac> pt(xx, yy);
			ss.insert(pt);
		}

		if (ss.size() == 0) continue;

		res += ss.size() - 1;
	}

	printf("%d\n", res);
}
