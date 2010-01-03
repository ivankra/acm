#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#define EPS 1e-9
using namespace std;

struct Point { double x, y; };

bool operator <(const Point &a, const Point &b) {
	return a.x < b.x-EPS || (a.x < b.x+EPS && a.y < b.y+EPS);
}

double cross(Point a, Point b, Point c) {
	return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

double dist(Point a, Point b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int main()
{
	vector<Point> p, h;
	int n;
	double len;

	for (int cs = 1; scanf("%d", &n) == 1 && n > 0; cs++) {
		printf("%sRegion #%d:\n", cs > 1 ? "\n" : "", cs);

		p.resize(n);
		for (int i = 0; i < n; i++) scanf("%lf %lf", &p[i].x, &p[i].y);

		sort(p.begin(), p.end());

		h.clear();
		for (int i = 0, k = 0; i < n; i++) {
			while (k >= 2 && cross(h[k-1], h[k-2], p[i]) < -EPS)
				h.pop_back(), k--;
			h.push_back(p[i]); k++;
		}

		len = 0;
		for (int i = 0; i < h.size()-1; i++)
			len += dist(h[i], h[i+1]);

		for (int i = 0; i < h.size(); i++)
			printf("%s(%.1f,%.1f)", i ? "-" : "", h[i].x, h[i].y);

		h.clear();
		for (int i = n-1, k = 0; i >= 0; i--) {
			while (k >= 2 && cross(h[k-1], h[k-2], p[i]) < -EPS)
				h.pop_back(), k--;
			h.push_back(p[i]); k++;
		}

		for (int i = 0; i < h.size()-1; i++)
			len += dist(h[i], h[i+1]);

		for (int i = 1; i < h.size(); i++)
			printf("-(%.1f,%.1f)", h[i].x, h[i].y);

		printf("\nPerimeter length = %.2f\n", len);
	}

	return 0;
}
