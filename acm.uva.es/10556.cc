#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <cmath>
#include <cassert>
#include <map>
using namespace std;

struct Point {
	double x, y;
};

Point P[100], Q[100], R[100];
int N;

double len(Point A, Point B) {
	double dx = A.x - B.x;
	double dy = A.y - B.y;
	return sqrt(dx*dx + dy*dy);
}

bool solve() {
	for (int flip = 0; flip < 1; flip++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// P[i]->Q[j], P[i+1]->Q[j+1]

				double scale = len(Q[j+1],Q[j]) / len(P[i+1],P[i]);

				double angle = atan2(Q[j+1].y-Q[j].y, Q[j+1].x-Q[j].x);
				angle -= atan2(P[j+1].y-P[j].y, P[j+1].x-P[j].x);
				double zx = cos(angle), zy = sin(angle);

				bool ok = true;
				for (int k = 0; k < N; k++) {
					double x = (P[k].x - P[i].x) * scale;
					double y = (P[k].y - P[i].y) * scale;

					// (x + y i)(zx + zy i)
					double xx = x * zx - y * zy;
					double yy = y * zx + x * zy;

					R[k].x = xx + Q[j].x;
					R[k].y = yy + Q[j].y;

					double t = len(R[k], Q[k]);
					if (t > 0.000001) { ok = false; break; }
				}
				if (ok) return true;
			}
		}

		reverse(Q, Q + N);
		Q[N] = Q[0];
	}
	return false;
}


int main()
{
	while (cin >> N) {
		if (N == 0) break;
		for (int i = 0; i < N; i++) cin >> P[i].x >> P[i].y;
		P[N] = P[0];
		for (int i = 0; i < N; i++) cin >> Q[i].x >> Q[i].y;
		Q[N] = Q[0];
		printf(solve() ? "similar\n" : "dissimilar\n");
	}
}
