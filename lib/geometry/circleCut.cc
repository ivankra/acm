#include <cmath>

double pi = 2*acos(0.0), eps = 1e-9;

/*
 *  Returns area of intersection of circle with center (0,0) of radius R with
 *  half plane to the right of line x=C.
 */
double cut(double R, double C) {
	if (C > R-eps) return 0;
	if (C < -R+eps) return pi*R*R;
	return acos(C/R)*R*R - sqrt(R*R-C*C)*C;
}

----

double EPS = 1e-9;
double PI = 2.0 * acos(0.0);

// \int_{-r}^{x} 2*sqrt(max(r^2 - t^2, 0)) dt
double Cut(double r, double x) {
	if (x < -r+EPS) return 0;
	if (x > r-EPS) return PI*r*r;

	return r*r*asin(x/r) + x*sqrt(r*r-x*x) + PI*r*r/2;
}
