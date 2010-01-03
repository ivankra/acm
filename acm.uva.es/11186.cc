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

int main() {
	int N, R;
	double theta[2000], PI=2*acos(0.0);
	double x[2000], y[2000], xsum[2000], ysum[2000];

	while (scanf("%d %d", &N, &R) == 2) {
		if (N == 0 && R == 0) break;

		for (int i = 1; i <= N; i++)
			scanf(" %lf", &theta[i]);
		sort(theta+1, theta+N+1);

		xsum[0] = ysum[0] = 0;
		for (int i = 1; i <= N; i++) {
			theta[i] *= PI / 180.0;
			x[i] = R * cos(theta[i]);
			y[i] = R * sin(theta[i]);
			xsum[i] = xsum[i-1] + x[i];
			ysum[i] = ysum[i-1] + y[i];
		}

		double res = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = i+1; j <= N; j++) {
				res += (N-j) * (x[i] * y[j] - x[j] * y[i]);
				res += x[j] * (ysum[N]-ysum[j]) - (xsum[N]-xsum[j]) * y[j];
				res += (xsum[N]-xsum[j]) * y[i] - x[i] * (ysum[N]-ysum[j]);
			}
		}
		res /= 2;

		printf("%.0f\n", res);
	}
}
