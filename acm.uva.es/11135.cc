#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

double Hypot(double dx, double dy) { return sqrt(dx*dx+dy*dy); }

int main()
{
	double D, L, xs, ys, xt, yt;
	double EPS = 1e-8;

	while (scanf("%lf %lf %lf %lf %lf %lf", &D, &L, &xs, &ys, &xt, &yt) == 6) {
		if (D < EPS) break;

		int row = (int)floor(ys/D), col = (int)floor(xs/D);
		ys -= row * D; xs -= col * D;
		yt -= row * D; xt -= col * D;

		xs -= D/2; ys -= D/2;
		xt -= D/2; yt -= D/2;
		if (yt < ys) { ys = -ys; yt = -yt; }
		if (xt < xs) { xs = -xs; xt = -xt; }
		//if (yt-ys < xt-xs) { swap(xs, ys); swap(xt, yt); }
		xs += D/2; ys += D/2;
		xt += D/2; yt += D/2;

		row = (int)floor(yt/D);
		col = (int)floor(xt/D);

		assert(0 <= row && row <= 305);
		assert(0 <= col && col <= 305);

		static double dp[512][512];

		for (int r = row; r >= 1; r--) {
			for (int c = col; c >= 1; c--) {
				double y1 = r * D + L;
				double x1 = c * D + L;

				int d = min(row-r, col-c);

				if (r == row || c == col) {
					dp[r][c] = Hypot(
						fabs(x1 - xt) - (col-c)*2*L,
						fabs(y1 - yt) - (row-r)*2*L
					);
				} else {
					dp[r][c] = 1e99;
					for (int i = 0; min(row-(r+i), col-c) == d; i++)
						dp[r][c] <?= Hypot(D-2*L, (i+1)*(D-2*L)) + dp[r+i+1][c+1];
					for (int i = 0; min(row-r, col-(c+i)) == d; i++)
						dp[r][c] <?= Hypot(D-2*L, (i+1)*(D-2*L)) + dp[r+1][c+i+1];
				}
			}
		}

		double swim = min(row, col)*sqrt(2.0)*2*L + abs(row-col)*2*L;
		double walk = 1e9;

		if (row == 0 && col == 0)
			walk = Hypot(xs-xt, ys-yt);

		for (int r = 0; r < row; r++) {
			for (int c = 0; (r == 0 || c == 0) && c < col; c++) {
				double y1 = r * D + D-L;
				double x1 = c * D + D-L;

				walk <?= Hypot(fabs(xs-x1)-c*2*L, fabs(ys-y1)-r*2*L) + dp[r+1][c+1];
			}
		}

		if (walk < EPS) walk = 0;
		if (swim < EPS) swim = 0;

		printf("The gopher has to swim %.2f meters and walk %.2f meters.\n", swim, walk);
	}
}
