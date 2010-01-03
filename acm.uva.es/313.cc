#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#define EPS 1e-9

struct Event {
	double x;
	int f;
	Event(double X, int F) : x(X), f(F) {}
	bool operator <(const Event &e) const { return x < e.x; }
};

double hyp(double x, double y) { return sqrt((x*x+y*y) >? 0.0); }

int main() {
	double bx, by;
	int N;
	while (scanf("%d %lf %lf", &N, &bx, &by) == 3 && N > 0) {
		vector<Event> v;

		for (int i = 0; i < N; i++) {
			double cx, cy, r;
			scanf("%lf %lf %lf", &cx, &cy, &r);

			double a = atan2(cy-by, cx-bx);
			double d = asin(r / hyp(cx-bx, cy-by));

			double x1 = bx - by / tan(a - d);
			double x2 = bx - by / tan(a + d);
			if (x1 > x2) swap(x1, x2);

			v.push_back(Event(x1, 1));
			v.push_back(Event(x2, -1));
		}

		sort(v.begin(), v.end());

		N = v.size();

		int m = 0;
		for (int i = 0; i < N;) {
			double x = v[i].x;
			int f = 0;

			for (; i < N && fabs(v[i].x - x) < EPS; i++)
				f += v[i].f;

			if (f > 0) {
				if (m == 0) printf("%.2f ", x-EPS);
				m += f;
			} else if (f < 0) {
				m += f;
				if (m <= 0) printf("%.2f\n", x-EPS);
			}
		}
		printf("\n");
	}
}
