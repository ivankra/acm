#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

struct pt { int x, y; };
pt operator -(pt a, pt b) { pt c={a.x-b.x,a.y-b.y}; return c; }

int skew(pt a, pt b) { return a.x * b.y - a.y * b.x; }
int dot(pt a, pt b) { return a.x * b.x + a.y * b.y; }
double len(pt a) { return sqrt(a.x * (double)a.x + a.y * (double)a.y); }

int main()
{
	pt p[1024];
	int i, j, k, n;
	double m, M, t, pi = 2 * acos(0.);

	while (scanf("%d", &n) == 1 && n >= 3) {
		for (i = 0; i < n; i++) scanf("%d %d", &p[i].x, &p[i].y);
		p[n] = p[0];
		p[n+1] = p[1];

		for (k = i = 0; i < n; i++) {
			j = skew(p[i+1]-p[i], p[i+2]-p[i]);
			if (j > 0) k++; else if (j < 0) k--;
		}

		if (k < 0) {
			for (i = 0, j = n-1; i < j; i++, j--)
				swap(p[i], p[j]);
			p[n] = p[0];
			p[n+1] = p[1];
		}

		for (i = 0; i < n; i++) {
			j = dot(p[i]-p[i+1], p[i+2]-p[i+1]);
			t = acos(j / (len(p[i]-p[i+1]) * len(p[i+2]-p[i+1])));
			if (skew(p[i+1]-p[i], p[i+2]-p[i]) < 0) t = 2 * pi - t;
			t *= 180 / pi;

			if (i == 0) {
				m = M = t;
			} else {
				m <?= t;
				M >?= t;
			}
		}

		printf("%.6f %.6f\n", m, M);
	}

	return 0;
}
