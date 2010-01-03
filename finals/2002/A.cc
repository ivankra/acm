#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
typedef long long LL;

struct Point {
	LL x, y, z;

	bool operator <(const Point &p) const {
		if (x != p.x) return x < p.x;
		if (y != p.y) return y < p.y;
		if (z != p.z) return z < p.z;
		return false;
	}
};

double dist(const Point &a, const Point &b) {
	double t = (a.x - b.x) * (a.x - b.x);
	t += (a.y - b.y) * (a.y - b.y);
	t += (a.z - b.z) * (a.z - b.z);
	return sqrt(t);
}

istream &operator >>(istream &is, Point &p) { return is >> p.x >> p.y >> p.z; }

int N;
double bestVol = 0, radius[10], PI=2*acos(0.0);
Point boxA, boxB, point[10];

void rec(int used, double curVol)
{
	int i, j;

	bestVol = max(bestVol, curVol);

	for (i = 0; i < N; i++) {
		if (used & (1 << i)) continue;

		Point p = point[i];
		if (p.x < boxA.x || p.x > boxB.x) continue;
		if (p.y < boxA.y || p.y > boxB.y) continue;
		if (p.z < boxA.z || p.z > boxB.z) continue;

		for (j = 0; j < N; j++)
			if ((used & (1 << j)) != 0 && dist(point[j], point[i]) < radius[j]) break;
		if (j < N) continue;

		double R = min(point[i].x - boxA.x, boxB.x - point[i].x);
		R = min(R, 0.0+min(point[i].y - boxA.y, boxB.y - point[i].y));
		R = min(R, 0.0+min(point[i].z - boxA.z, boxB.z - point[i].z));

		for (j = 0; j < N; j++) {
			if ((used & (1 << j)) != 0) {
				R = min(R, dist(point[i], point[j]) - radius[j]);
			}
		}
		if (R < 1e-9) continue;

		radius[i] = R;
		rec(used | (1 << i), curVol + PI*R*R*R*4/3);
	}
}

int main()
{
	for (int cs = 1; cin >> N >> boxA >> boxB; cs++) {
		if (N == 0) break;

		if (boxA.x > boxB.x) swap(boxA.x, boxB.x);
		if (boxA.y > boxB.y) swap(boxA.y, boxB.y);
		if (boxA.z > boxB.z) swap(boxA.z, boxB.z);

		for (int i = 0; i < N; i++) cin >> point[i];

		bestVol = 0;
		rec(0, 0);

		double res = (boxB.z - boxA.z);
		res *= boxB.y - boxA.y;
		res *= boxB.x - boxA.x;
		printf("Box %d: %.0lf\n\n", cs, res - bestVol);
	}
}
