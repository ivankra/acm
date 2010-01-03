#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long i64;

struct Point {
	i64 x, y;
	Point(i64 x, i64 y) : x(x), y(y) {}
};

bool operator <(const Point &a, const Point &b) { return a.x<b.x || (a.x==b.x && a.y<b.y); }
bool operator ==(const Point &a, const Point &b) { return a.x==b.x && a.y==b.y; }

Point rot(const Point &p) { return Point(-p.y, p.x); }

int main()
{
	i64 x, y, t;

	for (scanf("%lld", &t); t-- > 0;) {
		vector<Point> v;
		v.clear();
		while (scanf(" %lld , %lld", &x, &y) == 2 && x >= 0 && y >= 0)
			v.push_back(Point(x, y));

		vector<vector<Point> > vv;
		vv.clear();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < v.size(); j++) {
				v[j] = rot(v[j]);
				if (j == 0) { x = v[j].x; y = v[j].y; }
				x <?= v[j].x; y <?= v[j].y;
			}

			for (int j = 0; j < v.size(); j++) {
				v[j].x -= x; v[j].y -= y;
			}

			sort(v.begin(), v.end());

			vv.push_back(v);
		}

		x = 4;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < i; j++)
				if (vv[j] == vv[i]) { x--; break; }

		printf("%lld\n%s", x, t ? "\n" : "");
	}

	return 0;
}
