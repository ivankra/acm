#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
#include <deque>
using namespace std;

int main() {
	int N;
	double p, p_pow[512], q_pow[512];
	static double f[512][512], g[512][512], h[512][512];

	while (scanf("%d %lf", &N, &p) == 2 && N > 0) {
		p_pow[0] = q_pow[0] = 1;
		for (int k = 1; k <= N; k++) p_pow[k] = p_pow[k-1] * p;
		for (int k = 1; k <= N; k++) q_pow[k] = q_pow[k-1] * (1-p);

		for (int k = 0; k <= N; k++) { f[0][k] = 0; g[0][k] = 1; }
		f[0][0] = 1;

		for (int n = 1; n <= N; n++) {
			g[n][0] = f[n][0] = q_pow[n];
			f[n][n] = p_pow[n];
			g[n][n] = 1;

			for (int k = 1; k < n; k++) {
				f[n][k] = p_pow[k] * (1-p) * g[n-k-1][k];

				if (n == 1)
					h[n][k] = 0;
				else
					h[n][k] = (1-p)*f[n-1][k] + h[n-1][k] * p - p_pow[k] * (1-p) * f[n-k-1][k];

				//double H = 0;
				//for (int m = 0; m < k; m++)
				//	H += (1-p) * p_pow[m] * f[n-m-1][k];
				//printf("h[n=%d, k=%d] = %.5f   H=%.5f\n", n,k,h[n][k], H);

				f[n][k] += h[n][k];

				g[n][k] = g[n][k-1] + f[n][k];
			}

			for (int k = n+1; k <= N; k++) {
				f[n][k] = 0;
				g[n][k] = 1;
			}
		}

		double res = 0;
		for (int k = 0; k <= N; k++) {
//			printf("  P(max streak = %d) = %.5f\n", k, f[N][k]);
			res += f[N][k] * k;
		}
		printf("%.6f\n", res);
	}
}
