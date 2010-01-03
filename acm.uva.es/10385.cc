// ternary search
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

double EPS = 1e-6;

double t, v1[50], v2[50];
int n;

double g(int i, double r) {
	double k = t - r;
	return r / v1[i] + k / v2[i];
}

double f(double r) {
	double z = 1e20;
	for (int i = 0; i < n-1; i++) z = min(z, g(i,r));
	return (z - g(n-1,r)) * 3600;
}

int main()
{
	while (cin >> t >> n) {
		for (int i = 0; i < n; i++)
			cin >> v1[i] >> v2[i];

		double left = 0, right = t;
		while (right - left > 1e-6) {
			double a = (2 * left + right) / 3;
			double b = (left + 2 * right) / 3;
			if (f(a) < f(b) + EPS)
				left = a;
			else
				right = b;
		}

		double r = (left + right) / 2;
		double w = f(r);
		if (w < -EPS)
			printf("The cheater cannot win.\n");
		else
			printf("The cheater can win by %.0f seconds with r = %.2fkm and k = %.2fkm.\n",
				w < EPS ? 0 : w, r, t-r);
	}
}
