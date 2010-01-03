#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

struct Function {
	vector<double> x, y;
	int N;

	double operator()(double arg) {
		int i;
		for (i = 0; i < N-1 && x[i+1] < arg; i++);
		return y[i];
	}
};

bool read(Function &f)
{
	if (scanf("%d", &f.N) != 1) return false;
	f.x.resize(f.N);
	f.y.resize(f.N);
	double cur = 0, len;
	for (int i = 0; i < f.N; i++) {
		f.x[i] = cur;
		scanf("%lf %lf", &f.y[i], &len);
		cur += len;
	}
	assert(fabs(cur - 10) < 0.0001);
	return true;
}


int main()
{
	Function f, g;
	while (read(f) && read(g)) {
		vector<double> x = f.x;
		for (int i = 0; i < g.N; i++) x.push_back(g.x[i]);
		x.push_back(0);
		x.push_back(10);
		sort(x.begin(), x.end());

		double res = 1e20;
		for (int i = 0; i+1 < x.size(); i++) {
			double h = x[i+1] - x[i];
			if (h < 1e-6) continue;
			double mid = (x[i+1] + x[i]) / 2;
			res = min(res, max(f(mid), g(mid)));
		}
		printf("%.3f\n", res);
	}
}
