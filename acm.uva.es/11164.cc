#include <algorithm>
#include <vector>
#include <sstream>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cctype>
using namespace std;

double a, b, c, EPS=1e-9;

bool solve() {
	if (a < EPS) a = 0;
	if (b < EPS) b = 0;
	if (c < EPS) c = 0;
	if (fabs(b) < EPS) return false;

	//a + x = b/(b+c) (a + x + y);
	//c + y = b/(b+a) (c + x + y);

	double a1 = c/(b+c), b1 = -b/(b+c), c1 = a*b/(b+c)-a;
	double a2 = -b/(a+b), b2 = a/(a+b), c2 = b*c/(a+b)-c;
	double det = a1*b2-a2*b1;
	//printf("det=%.5f\n",det);
	if (fabs(det) < EPS) return false;

	double x = (c1*b2-c2*b1)/det;
	double y = (a1*c2-a2*c1)/det;
	//printf("x=%.5f y=%.5f\n",x,y);
	if (x < -EPS || y < -EPS) return false;

	if (x < EPS) {
		if (a > EPS) return false;
		x = 0;
	}

	if (y < EPS) {
		if (c > EPS) return false;
		y = 0;
	}

	printf("%.4f\n", x+y);
	return true;
}

int main()
{
	for (int cs = 1; scanf(" %lf %lf %lf", &a, &b, &c) == 3 && a > -0.1; cs++) {
		printf("Set %d:\n", cs);
		if (!solve()) printf("Poor King!\n");
	}
}
