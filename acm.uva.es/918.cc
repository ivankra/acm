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
#include <complex>
using namespace std;

double EPS = 1e-9;

int eval(double x0, double y0)
{
	complex<double> c(x0, y0), z(0, 0);
	int i = 0;
	do {
		z = z * z + c;
		i++;
	} while (i <= 12 && abs(z) < 2+EPS);
	return i-1;
}

int main()
{
	int T;
	scanf("%d", &T);

	char chars[100];
	double mini, maxi, preci, minr, maxr, precr;

	for (int cs = 1; cs <= T; cs++) {
		scanf(" \"%[^\"]\" %lf %lf %lf %lf %lf %lf",
			chars, &mini, &maxi, &preci, &minr, &maxr, &precr);

		chars[12] = ' ';
		for (double y = mini; y < maxi + EPS; y += preci) {
			for (double x = minr; x < maxr + EPS; x += precr) {
				putchar(chars[eval(x, y)]);
			}
			printf("\n");
		}
		if (cs != T) printf("\n");
	}
}
