#include <stdio.h>
#include <math.h>

#define EPS 1e-9

typedef struct { double x, y; } pt;

double sq(double x) { return x * x; }
double d2(pt A, pt B) { return sq(A.x - B.x) + sq(A.y - B.y); }
double d(pt A, pt B) { return sqrt(d2(A, B)); }

int main()
{
	pt A, B, C, R, M;
	double t, u;
	int n;

	while (scanf("%lf %lf %d %lf %lf", &M.x, &M.y, &n, &A.x, &A.y) == 5) {
		R = A;

		while (n-- > 0 && scanf("%lf %lf", &B.x, &B.y) == 2) {
			u = d(A,B);
			if (u < EPS) {
				C = A;
			} else {
				t = (d2(A,M) + d2(A,B) - d2(B,M)) / (2 * u);
				if (t < 0 || t > u) {
					C = A;
				} else {
					C.x = A.x + t / u * (B.x - A.x);
					C.y = A.y + t / u * (B.y - A.y);
				}
			}
			if (d2(A,M) < d2(C,M)) C = A;
			if (d2(B,M) < d2(C,M)) C = B;
			if (d2(C,M) < d2(R,M)) R = C;
			A = B;
		}

		printf("%.4f\n%.4f\n", R.x, R.y);
	}

	return 0;
}
