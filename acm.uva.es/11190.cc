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

struct Fuzzy {
	double m;
	long long e;
};

Fuzzy operator +(Fuzzy x, Fuzzy y) {
	if (x.e < y.e) swap(x, y);

	x.m += y.m * pow(10.0, double(y.e-x.e));
	while (x.m >= 10.0-1e-9) {
		x.m /= 10;
		x.e++;
	}
	return x;
}

int main() {
	int a, b, k;
	for (int cs = 1; scanf("%d %d %d", &a, &b, &k) == 3; cs++) {
		if (a < 0 || b < 0 || k < 0) break;
		if (a <= 0) a = 1;

		Fuzzy res = { 0, 0 };
		for (int n = b; n >= a; n--) {
			Fuzzy pw;
			double t = k * log10(double(n));
			pw.e = (long long)floor(t);
			pw.m = pow(10.0, t-pw.e);

			res = res + pw;

			//printf("%d^%d = %.10lfe%lld\n", n, k, pw.m, pw.e);
		}

		while (res.m >= 1.0-1e-6) { res.m /= 10.0; res.e++; }
		if (res.m < 1e-6) { res.m = 0; res.e = 1; }
		printf("Case %.4d: %.6fe%.10lld\n", cs, res.m, res.e);
	}
}
