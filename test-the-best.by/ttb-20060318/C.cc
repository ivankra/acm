#include <cmath>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

double pi = 2*acos(0.0), eps = 1e-9;

struct FoundationForSkyscraper {
	double cut(double R, double C) {
		if (C > R-eps) return 0;
		if (C < -R+eps) return pi*R*R;
		return acos(C/R)*R*R - sqrt(R*R-C*C)*C;
	}

	double ar(double W, double H, double R) {
		double S = pi*R*R/4;
		if (W < eps || H < eps || R < eps) return 0;
		if (W*W+H*H < R*R+eps) return W*H;
		return S - cut(R,H)/2 - cut(R,W)/2;
	}

	string getMaxDistance (int W, int H, int x0, int y0, int D, int T) {
		double a = 1e-5, b = (W+H)*2;
		for (int k = 0; k < 100; k++) {
			double R = (a + b) / 2;
			double S = ar(W-x0,H-y0,R) + ar(x0,y0,R) + ar(x0,H-y0,R) + ar(W-x0,y0,R);
			if (S > D*T) b = R; else a = R;
		}

		char s[16];
		sprintf(s, "%.3f", (a+b)/2);
		return string(s);
	}
};
