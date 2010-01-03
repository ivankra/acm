// p[k] = (N-1)!/(N-k)! k/N^k
// p[k] = p[k-1] * m[k], m[k] = k/(k-1) (n-k-1)/n, (m[k] = multiplicative factor)
// solve for m[k] < 1.
#include <cstdio>
#include <cmath>

int main() {
	int N;
	while (scanf("%d", &N) == 1 && N > 0) {
		double x = (sqrt(1+4.0*N) - 1) / 2.0;
		printf("%.2f %.0f\n", x, floor(x+1+1e-9));
	}
}
