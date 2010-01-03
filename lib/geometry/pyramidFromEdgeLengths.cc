#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

int main()
{
	double AB, AC, AD, BC, BD, CD;
	cin >> AB >> AC >> AD >> BC >> BD >> CD;

	double Cx = AC * (-BC*BC + AB*AB + AC*AC) / (2*AB*AC);
	double Cy = sqrt(AC*AC - Cx*Cx);

	// A(0, 0, 0)
	// B(AB, 0, 0)
	// C(Cx, Cy, 0)
	// D(x, y, z)
	double x = (BD*BD - AD*AD - AB*AB) / (-2*AB);
	double y = (CD*CD - AD*AD - Cx*Cx - Cy*Cy + 2*Cx*x) / (-2*Cy);
	double z = sqrt(AD*AD - x*x - y*y);

	double ABC = Cy * AB / 2;
	double V = ABC * z / 3;
	printf("%.4f\n", V);
}
