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

double PI = 2.0 * acos(0.0);
double w, h;

int main()
{
	while (scanf("%lf %lf", &w, &h) == 2 && w > 0.5) {
		if (w > h) swap(w, h);

		double best = 0;

		double r = w/(2*PI);
		best >?= PI * r*r *(h - 2*r);

		double r_max = min(w/2.0, h / (2*PI + 2));
		best >?= PI * r_max * r_max * w;

		printf("%.3f\n", best);
	}
}
