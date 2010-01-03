#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
using namespace std;

int x[10000], y[10000], r[10000];

double sq(double t) { return t*t; }

bool check(int n)
{
	double x0 = x[n-1], y0 = y[n-1];
	double u = sq(r[n-1]);

	for (int i = n-2; i >= 0; i--) {
		if (sq(x[i]-x0) + sq(y[i]-y0) > sq(r[i])-1e-6) return false;

		double v = sq(r[i]);
		double x1 = (x0 * u + x[i] * v) / (u + v);
		double y1 = (y0 * u + y[i] * v) / (u + v);
		x0 = x1; y0 = y1; u += v;
	}

	return true;
}

int main()
{
	int N;
	while (scanf("%d", &N) == 1 && N > 0) {
		for (int i = 0; i < N; i++)
			scanf("%d %d %d", &x[i], &y[i], &r[i]);

		int k;
		for (k = 2; k <= N; k++)
			if (!check(k)) break;
		printf(k <= N ? "Unfeasible %d\n" : "Feasible\n", k-1);
	}
}
