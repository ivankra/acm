#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define EPS 1e-6

int N, L, W;
struct Seg {
	double a, b;
	bool operator <(const Seg &z) const { return a < z.a; }
} s[10010];

double sq(double x) { return x*x; }

int main() {
	while (scanf("%d %d %d", &N, &L, &W) == 3) {
		for (int i = 0; i < N; i++) {
			double x; int r;
			scanf("%lf %d", &x, &r);
			if (2*r <= W) { N--; i--; continue; }

			double d = sqrt(sq(r) - sq(W/2.0));
			s[i].a = x - d;
			s[i].b = x + d;
			if (s[i].b < EPS) { N--; i--; continue; }
		}

		sort(s, s+N);

/*		printf("cover [0,%.1f] with {", (double)L);
		for (int i = 0; i < N; i++)
			printf("%s[%.2f, %.2f]", i?", ":"", s[i].a, s[i].b);
		printf("}\n");
*/
		double C = 0, M = 0;
		int res = 0;

		for (int i = 0; i < N && C < L-EPS; i++) {
//printf("i=%d C=%.2f M=%.2f;  considering [%.2f, %.2f]\n",i,C,M,s[i].a,s[i].b);
			if (s[i].a < C+EPS) {
				M >?= s[i].b;
			} else if (s[i].a < M+EPS) {
				res++;
				C = M;
				M >?= s[i].b;
			} else {
				res = -1;
				break;
			}
		}
//printf("C=%.2f M=%.2f\n",C,M);

		if (C < L-EPS && M > L-EPS && res >= 0) { res++; C = M; }

		if (C < L-EPS) res = -1;
		printf("%d\n", res);
	}
}
