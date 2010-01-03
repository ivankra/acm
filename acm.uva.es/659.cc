#include <cstdio>
#include <cmath>
#define EPS 1e-9
using namespace std;

struct Point {
	long double x, y;
	Point(long double x=0, long double y=0) : x(x), y(y) {}
	Point operator +(const Point &b) const { return Point(x+b.x, y+b.y); }
	Point operator -(const Point &b) const { return Point(x-b.x, y-b.y); }
	Point operator *(long double c) const { return Point(x*c, y*c); }
};

long double dot(Point a, Point b) { return a.x*b.x+a.y*b.y; }

int main()
{
	Point A, D, C[64];
	long double R[64];
	int s, n;

	for (int cs = 1; scanf("%d", &n) == 1 && n > 0; cs++) {
		printf("Scene %d\n", cs);
		for (int i = 0; i < n; i++)
			scanf(" %Lf %Lf %Lf", &C[i].x, &C[i].y, &R[i]);

		scanf("%Lf %Lf %Lf %Lf", &A.x, &A.y, &D.x, &D.y);

		for (int k = 0;; k++) {
			long double t = -1;
			D = D * (1. / sqrt(dot(D, D)));
			s = -1;

			for (int i = 0; i < n; i++) {
				long double b = 2 * dot(D, A-C[i]);
				long double c = dot(A-C[i],A-C[i])-R[i]*R[i];
				long double d = b*b-4*c;
				if (d < EPS) continue;

				d = sqrt(d);

				long double u = (-b-d)/2;
				if (u < EPS) u = (-b+d)/2;
				if (u < EPS) continue;
				if (s >= 0 && u > t) continue;
				t = u;

				s = i;
			}

			if (k > 0) printf(" ");
			if (s < 0) { printf("inf\n"); break; }
			if (k == 10) { printf("...\n"); break; }

			printf("%d", s+1);

			Point B = A + D * t;
			Point nm = B - C[s];
			Point N = B + nm * (dot(A-B, nm) / dot(nm, nm));
			D = A + (N - A) * 2 - B;
			A = B;
		}

		printf("\n");
	}

	return 0;
}
