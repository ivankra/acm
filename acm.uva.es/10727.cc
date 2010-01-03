// System of equations:
//   sum p_i = sum w_i
//   sum n_i p_i = sum n_i w_i

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
using namespace std;

int n[200], w[200], N;
double a, b;

double p(int i, int d) { 
	double t = exp(a + b * n[i]);
	if (d == 0)
		return 1 - 1 / (1 + t);
	else if (d == 1)                        // d/da
		return t / ((1+t)*(1+t));
	else                                    // d/db
		return n[i]*t / ((1+t)*(1+t));
}

double f(int k, int d) {
	double res = 0;
	for (int i = 0; i < N; i++)
		res += (p(i, d) - (d==0?w[i]:0)) * (k==0?1:n[i]);
	return res;
}

int main() {
	while (scanf("%d", &N) == 1 && N > 0) {
		for (int i = 0; i < N; i++) scanf("%d %d", &n[i], &w[i]);

		// Newton-Raphson's method

		a = 0; b = 0;
		for (int k = 0; k < 50; k++) {
			double J[2][2] = {   // jacobian
				{ f(0, 1), f(0, 2) },
				{ f(1, 1), f(1, 2) }
			};

			double det = J[0][0] * J[1][1] - J[0][1] * J[1][0];
			double JI[2][2] = {  // jacobian's inverse
				{ J[1][1]/det, -J[1][0]/det },
				{ -J[0][1]/det, J[0][0]/det }
			};

			double F[2] = { f(0, 0), f(1, 0) };

			a -= (JI[0][0] * F[0] + JI[0][1] * F[1]);
			b -= (JI[1][0] * F[0] + JI[1][1] * F[1]);
		}

		printf("%.4f %.4f\n", a, b);
	}
}
