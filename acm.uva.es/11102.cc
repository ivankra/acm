#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

double EPS = 1e-6;
double PI = 2.0 * acos(0.0);

double Cut(double r, double x) {
	if (x < -r+EPS) return -PI*r*r/2.0;
	if (x > r-EPS) return PI*r*r/2.0;

	return r*r*asin(x/r) + x*sqrt(r*r-x*x);
}

double CutS(double r, double s) {
	return Cut(r, -r + s) - Cut(r, -r);
}

double baseHeight, baseDiam, baseRad;
double neckHeight, neckDiam, neckRad;
double shoulderHeight, totalHeight;

double f_slope, f_s;

double f(double z) {
	double r = max(0.0, baseRad - f_slope * z);
	return Cut(r, baseRad) - Cut(r, baseRad - f_s);
}

double Integrate(double a, double b) {
	int n = 5000;
	double h = (b - a) / n;
	double x = a + h/2, res = 0;
	for (int i = 0; i < n; i++, x += h) {
		res += f(x);
	}
	return res * h;
}

double SideVolume(double s) {
	double res = 0;
	if (s < EPS) return 0;

	res += baseHeight * CutS(baseRad, s);
	res += neckHeight * CutS(neckRad, s - (baseRad - neckRad));

	if (shoulderHeight > EPS) {
		f_slope = (baseRad - neckRad) / shoulderHeight;
		f_s = s;
		res += Integrate(0, shoulderHeight);
	}

	return res;
}

double VerticalVolume(double liquid) {
	double res = 0;

	if (liquid > EPS) {
		double h = min(liquid, baseHeight);
		res += h * PI * baseRad * baseRad;
		liquid -= h;
	}

	if (liquid > EPS && shoulderHeight > EPS) {
		double h = min(liquid, shoulderHeight);
		if (fabs(baseRad - neckRad) < EPS) {
			res += h * PI * baseRad * baseRad;
		} else {
			double h2 = baseRad/(baseRad-neckRad)*shoulderHeight;
			double r2 = baseRad;
			double h1 = h2 - h;
			double r1 = baseRad + (neckRad - baseRad) * h / shoulderHeight;
			res += (PI*r2*r2*h2 - PI*r1*r1*h1) / 3.0;
		}
		liquid -= h;
	}

	if (liquid > EPS && neckHeight > EPS) {
		double h = min(liquid, neckHeight);
		res += h * PI * neckRad * neckRad;
		liquid -= h;
	}

	return res;
}

int main()
{
	string s;
	double h;

	while (getline(cin, s)) {
		if (s.size() < 11 || s.substr(0, 11) == "0 0 0 0 0 0") break;

		istringstream is(s);
		is >> h >> baseHeight >> baseDiam;
		is >> neckHeight >> neckDiam >> totalHeight;

		baseRad = baseDiam / 2.0;
		neckRad = neckDiam / 2.0;
		shoulderHeight = totalHeight - baseHeight - neckHeight;

		double vol = VerticalVolume(h);

		double left = 0, right = baseDiam;
		while (right - left > 1e-9) {
			double mid = (left + right) / 2;
			if (SideVolume(mid) > vol)
				right = mid;
			else
				left = mid;	
		}
		printf("%.2f\n", left);
	}
}
