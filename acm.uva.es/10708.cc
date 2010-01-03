#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

//#define dprintf printf
void dprintf(...){}

double PI = 2*acos(0.0), EPS = 1e-9;

struct LinearTargeting {
	long long Cx, Cy, Cv;	// hunter's coordinates and speed
	long long Px, Py, Pv;	// pray
	double Pdx, Pdy;		// pray's speed vector
	double res_angle, res_time, res_x, res_y;

	double normAngle(double a) {
		while (a > 2*PI) a -= 2*PI;
		while (a < 0) a += 2*PI;
		if (fabs(a) < EPS) a = 0;
		if (fabs(a - 2*PI) < EPS) a = 0;
		return a;
	}

	bool solve() {
		long long dist2 = (Cx-Px)*(Cx-Px) + (Cy-Py)*(Cy-Py);

		// special cases
		res_angle = res_time = 0;
		res_x = Px; res_y = Py;
		if (dist2 == 0) return true;
		if (Cv == 0) return false;
		if (Pv == 0) {
			res_angle = normAngle(atan2(Py-Cy, Px-Cx));
			res_time = sqrt(dist2+0.0) / Cv;
			return true;
		}

		long long a = (Pv*Pv - Cv*Cv);
		double b = 2*Pdx*(Px-Cx) + 2*Pdy*(Py-Cy);
		long long c = dist2;

		dprintf("C=(%.3f, %.3f)\n", Cx+0.0, Cy+0.0);
		dprintf("P=(%.3f, %.3f)  Pdx=%.3f Pdy=%.3f\n", Px+0.0, Py+0.0,Pdx,Pdy);
		dprintf("a=%lld b=%.3lf c=%lld\n",a,b,c);

		if (a == 0) {
			// linear equation case
			if (fabs(b) < EPS) return false;
			res_time = -(c / b);
		} else {
			// quadratic case
			double det = b*(double)b - 4*a*c;
			if (fabs(det) < EPS) det = 0;
			else if (det < EPS) return false;
			else det = sqrt(det);

			double t1 = (-b - det) / (2.0 * a);
			double t2 = (-b + det) / (2.0 * a);
			if (t1 > t2) swap(t1, t2);

			res_time = -1;
			if (t1 > EPS) res_time = t1;
			else if (t2 > EPS) res_time = t2;
		}

		if (res_time < EPS) return false;

		res_x = Px + res_time * Pdx;
		res_y = Py + res_time * Pdy;
		res_angle = normAngle(atan2(res_y - Cy, res_x - Cx));

		dprintf("M=(%.5f, %.5f)\n", res_x, res_y);
		dprintf("CM/Cv = %.5f\n", sqrt((res_x-Cx)*(res_x-Cx)+(res_y-Cy)*(res_y-Cy))/Cv);
		dprintf("PM/Pv = %.5f\n", sqrt((res_x-Px)*(res_x-Px)+(res_y-Py)*(res_y-Py))/Pv);

		return 1;
	}
};

int main()
{
	long long T, Pdeg, maxTime;
	LinearTargeting z;
	for (cin >> T; T--;) {
		cin >> z.Cx >> z.Cy >> z.Px >> z.Py >> Pdeg >> z.Pv >> z.Cv >> maxTime;
		z.Pdx = z.Pv * cos(Pdeg*PI/180);
		z.Pdy = z.Pv * sin(Pdeg*PI/180);
		if (!z.solve() || z.res_time > maxTime+EPS) {
			printf("sorry, buddy\n");
		} else {
			if (fabs(z.res_time) < EPS) z.res_time = 0;
			if (fabs(z.res_x) < EPS) z.res_x = 0;
			if (fabs(z.res_y) < EPS) z.res_y = 0;
			printf("%.2f %.2f %.2f %.2f\n",
				z.res_angle*180/PI, z.res_time, z.res_x, z.res_y);
		}
	}
}
