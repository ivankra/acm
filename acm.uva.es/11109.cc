#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int main()
{
	int k;
	double b, w, r, c, EPS = 1e-6;

	while (scanf("%d %lf %lf %lf %lf", &k, &b, &w, &r, &c) == 5 && k > 0) {
		if (b + w < r+EPS) {
			printf("0\n");
			continue;
		}

		double t = (b + w - r) / k;

		double x = t-w+r;
		if (x > c-w) x = c - w;
		if (x > b) x = b;
		if (x < EPS) x = 0;

		double y = (k > 1 ? (b-x)/(k-1) : 0);
		if (y > c-r) y = c - r;
		if (y < EPS) y = 0;

		printf("%d %.9lf", k, x);
		for (int i = 1; i < k; i++)
			printf(" %.9lf", y);
		printf("\n");
	}
}
