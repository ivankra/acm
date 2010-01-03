// ICPC Finals 2003 - Problem E - Covering Whole Holes
//
// If there exists a covering, then there is one, in which
// some cover's horizontal side touches some hole's horizontal side.
// So, we can solve the problem by checking about 25^2 = 625 vertical
// shifts, and for each of them determining whether or not it is possible
// to cover the hole by doing just a horizontal shift.
//
// To do that, first find the set of vertical sides of both
// polygons and determine their types ("left" or "right").
// Imagine that the hole is fixed, and the cover is continuously moved
// from x=-infinity to x=+infinity. We do sweeping on its movement,
// and determine the area of the hole, which is covered at any given
// moment of time. The rate of change of this area is constant, except
// at moments when some cover's side overlaps some hole's side. At these
// moments the rate of change changes by a constant, depending on types
// of the overlapping sides and length of overlap.
//
// Covering is possible if at some moment of time the hole was
// covered completely, i.e. covered area was equal to the hole's area.
//
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;
#define FOREACH(it,x) for(__typeof((x).begin()) it = (x).begin(); it != (x).end(); ++it)
typedef pair<int, int> PII;
typedef long long LL;

struct Point {
	int x, y;
};

struct VSide {
	int x, y1, y2;
	int kind;  // +1=left, -1=right
};

struct Polygon {
	Point p[100];
	int n;
	LL area;

	VSide vside[100];
	int nv;

	void makeSides() {
		p[n] = p[0];
		nv = 0;
		for (int i = 0; i < n; i++) {
			if (p[i].x != p[i+1].x) continue;
			vside[nv].x = p[i].x;
			vside[nv].y1 = p[i].y;
			vside[nv].y2 = p[i+1].y;
			vside[nv].kind = (p[i].y > p[i+1].y ? +1 : -1);
			nv++;
		}
	}
};

Polygon Hole, Cover;

struct Event {
	int dx, da;

	bool operator <(const Event &e) const {
		return dx < e.dx;
	}
};

int check1D()
{
	Hole.makeSides();
	Cover.makeSides();

	vector<Event> events;
	for (int i = 0; i < Cover.nv; i++) {
		for (int j = 0; j < Hole.nv; j++) {
			VSide &cs = Cover.vside[i];
			VSide &hs = Hole.vside[j];

			int commonA = max(min(cs.y1, cs.y2), min(hs.y1, hs.y2));
			int commonB = min(max(cs.y1, cs.y2), max(hs.y1, hs.y2));
			if (commonB <= commonA) continue;

			Event e;
			e.dx = hs.x - cs.x;
			e.da = (hs.kind * cs.kind * -1) * (commonB - commonA);
			events.push_back(e);
		}
	}

	sort(events.begin(), events.end());
	if (events.size() == 0) return 0;

	LL covered = 0, delta = 0;
	int curDX = events[0].dx;

	FOREACH(it, events) {
		if (covered >= Hole.area) return 1;

		Event &e = *it;
		if (e.dx != curDX) {
			covered += delta * (LL)(e.dx - curDX);
			curDX = e.dx;
		}

		delta += e.da;
	}

	return 0;
}

int solve()
{
	if (Hole.area > Cover.area) return 0;

	set<LL> dy_set;
	for (int i = 0; i < Hole.n; i++)
		for (int j = 0; j < Cover.n; j++)
			dy_set.insert(Hole.p[i].y - Cover.p[j].y);

	FOREACH(it, dy_set) {
		LL dy = *it;
		for (int j = 0; j < Cover.n; j++) Cover.p[j].y += dy;
		if (check1D()) return 1;
		for (int j = 0; j < Cover.n; j++) Cover.p[j].y -= dy;
	}

	return 0;
}

void readPoly(Polygon &poly)
{
	Point *p = poly.p;
	for (int i = 0; i < poly.n; i++)
		scanf("%d %d", &p[i].x, &p[i].y);

	poly.area = 0;
	p[poly.n] = p[0];
	for (int i = 0; i < poly.n; i++)
		poly.area += p[i].x * (LL)p[i+1].y - p[i+1].x * (LL)p[i].y;
	if (poly.area < 0) {
		reverse(p, p + poly.n);
		poly.area = -poly.area;
	}
	assert(poly.area % 2 == 0);
	poly.area /= 2;

	int del[100];
	for (int i = 0; i < poly.n; i++) {
		Point &a = p[(i+poly.n-1)%poly.n];
		Point &b = p[i];
		Point &c = p[(i+1)%poly.n];

		del[i] = 0;
		if ((a.x-c.x)*(LL)(b.y-c.y) == (a.y-c.y)*(LL)(b.x-c.x))
			del[i] = 1;
	}

	int j = 0;
	for (int i = 0; i < poly.n; i++)
		if (!del[i]) p[j++] = p[i];
	poly.n = j;
	p[poly.n] = p[0];
}

int main()
{
	int cs = 1;
	while (scanf("%d %d", &Hole.n, &Cover.n) == 2) {
		if (Hole.n <= 0 || Cover.n <= 0) break;
		readPoly(Hole);
		readPoly(Cover);
		printf("Hole %d: %s\n", cs, solve() ? "Yes" : "No");
		cs++;
	}
}

