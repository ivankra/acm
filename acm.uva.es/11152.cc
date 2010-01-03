#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

int main()
{
	double PI = 2*acos(0.0);
	double a, b, c;
	while (scanf(" %lf %lf %lf", &a, &b, &c) == 3) {
		double s = (a+b+c)/2;
		double S = sqrt(s*(s-a)*(s-b)*(s-c));

		double r = S / s;
		double R = a*b*c / (4 * r * s);

		double ros = PI*r*r;
		double vio = S - ros;
		double sun = PI*R*R - S;
		printf("%.4f %.4f %.4f\n", sun, vio, ros);


	}
}
