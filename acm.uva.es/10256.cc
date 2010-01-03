#include <cstdio>
#include <algorithm>
using namespace std;

struct Point {
	int x, y;
	bool operator <(const Point &q) const {
		return x<q.x || (x==q.x && y<q.y);
	}
};

int cross(const Point &o, const Point &a, const Point &b) {
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}

void hull(Point P[], int &N) {
	sort(P, P+N);

	Point h[1024];
	int m = 0;
	for (int k = 0; k < N; k++) {
		while (m >= 2 && cross(h[m-2], h[m-1], P[k]) <= 0) m--;
		h[m++] = P[k];
	}

	int t = m-1;
	for (int k = N-2; k >= 0; k--) {
		while (m-t >= 2 && cross(h[m-2], h[m-1], P[k]) <= 0) m--;
		h[m++] = P[k];
	}

	N = m-1;
	for (int i = 0; i < m; i++) P[i] = h[i];
}

int in(const Point &p, Point P[], int N) {
	for (int i = 0; i < N; i++)
		if (cross(p, P[i], P[i+1]) < 0) return 0;
	return 1;
}

int main() {
	Point P[1024], Q[1024];
	int N, M;
	while (scanf("%d %d", &N, &M) == 2 && N > 0 && M > 0) {
		for (int i = 0; i < N; i++) scanf("%d %d", &P[i].x, &P[i].y);
		for (int i = 0; i < M; i++) scanf("%d %d", &Q[i].x, &Q[i].y);

		hull(P, N);
		hull(Q, M);

		for (int ord = 0; ord < 2; ord++) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; ; j++) {
					if (j == M) goto yes;
					if (cross(Q[j], P[i], P[i+1]) >= 0) break;
				}
			}

			if (N == 2) {
				int s = cross(Q[0], P[0], P[1]);
				for (int i = 0;; i++) {
					if (i == M) goto yes;

					int d = cross(Q[i], P[0], P[1]);
					if (d == 0) break;
					if (s<0 && d>0) break;
					if (s>0 && d<0) break;
				}
			}

			swap(N, M);
			for (int i = 0; i < 1024; i++) swap(P[i], Q[i]);
		}

		printf("No\n");
		continue;
yes:		printf("Yes\n");

	}
}
