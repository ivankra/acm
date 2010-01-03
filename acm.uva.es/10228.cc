// nested ternary search
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

struct Point {
	double x, y;
};

Point P[200];
int N;

double f(double x, double y) {
	double res = 0;
	for (int i = 0; i < N; i++) {
		double dx = x - P[i].x;
		double dy = y - P[i].y;
		res += sqrt(dx*dx +dy*dy);
	}
	return res;
}

double findY(double x)
{
	double left = 0, right = 10000;
	for (int k = 0; k < 20; k++) {
		double a = (6 * left + 4 * right) / 10;
		double b = (4 * left + 6 * right) / 10;
		if (f(x, a) > f(x, b))
			left = a;
		else
			right = b;
	}
	return f(x, (left + right) / 2);
}

double findX()
{
	double left = 0, right = 10000;
	for (int k = 0; k < 20; k++) {
		double a = (6 * left + 4 * right) / 10;
		double b = (4 * left + 6 * right) / 10;
		if (findY(a) > findY(b))
			left = a;
		else
			right = b;
	}
	return findY((left + right) / 2);
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%lf %lf", &P[i].x, &P[i].y);
		}
		if (cs != 1) printf("\n");
		printf("%.0f\n", findX());
	}
}
