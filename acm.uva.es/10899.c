#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*#define dprintf printf*/
void dprintf(char *s, ...) { }

#define EPS 1e-8

typedef struct { double x, y, dx, dy; } pt_t;

double height, width, vel0, stop, decel;
pt_t S, Q;

double len(pt_t A, pt_t B)
{
	return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

double fmin(double a, double b)
{
	return (a < b) ? a : b;
}

/* shortest distance from segment AB to Q */
double qdist(pt_t A, pt_t B)
{
	double a, b, q, t, r;
	double cos_a, cos_b;

	a = len(B, Q);
	b = len(A, Q);
	q = len(A, B);

	r = fmin(a, b);

	cos_a = (b * b + q * q - a * a) / (2. * b * q);
	cos_b = (a * a + q * q - b * b) / (2. * a * q);
	if (cos_a > -EPS && cos_b > -EPS) {
		t = b * sqrt(1. - cos_a * cos_a);
		r = fmin(r, t);
	}

	return r;
}

double posiroot(double a, double b, double c)
{
	double D, x1, x2;

	D = b * b - 4 * a * c;
	if (D < -EPS) { dprintf("posiroot: D=%.5f\n", D); abort(); }

	D = sqrt(D);

	if (D < EPS) {
		x1 = x2 = -b / (2. * a);
		if (x1 < -EPS) { dprintf("posiroot: D=0, x=%.5f\n", x1); abort(); }
		if (x1 < EPS) x1 = 0.;
		return x1;
	} else {
		x1 = (-b + D) / (2. * a);
		x2 = (-b - D) / (2. * a);

		if (fabs(x1) < EPS) x1 = 0.;
		if (fabs(x2) < EPS) x2 = 0.;

		if (x1 > -EPS && x2 > -EPS) { dprintf("posiroot: multiple positive roots %.5f, %.5f; choosing smaller\n",x1,x2); }
		if (x1 < 0 && x2 < EPS) { dprintf("posiroot: no positive roots\n"); abort(); }

		return (x1 < x2) ? x1 : x2;
	}
}

double sim()
{
	pt_t A, B;
	double tm, vel, shortest;
	double d, u, t, z;

	shortest = len(S, Q);

	A = S;
	tm = 0;
	vel = vel0;
	decel = vel0 / stop;

	while (vel > EPS) {
dprintf("*** sim step: A=(%.5f,%.5f) v=(%.5f,%.5f) t=%.5f |v|=%.5f\n",
	A.x, A.y, A.dx, A.dy, tm, vel);

		d = 1. / 0.;

		if (fabs(A.dx) > EPS) {
			u = -A.x / A.dx;
			if (u > EPS) d = fmin(d, u);

			u = (width - A.x) / A.dx;
			if (u > EPS) d = fmin(d, u);
		}

		if (fabs(A.dy) > EPS) {
			u = -A.y / A.dy;
			if (u > EPS) d = fmin(d, u);

			u = (height - A.y) / A.dy;
			if (u > EPS) d = fmin(d, u);
		}

dprintf("distance before next collision: %.5f\n", d);

		if (d > 1e50) {
			dprintf("mistake?\n");
			abort();
		}


dprintf("decel=%.5f vel=%.5f\n",decel,vel);

		t = vel / decel;
		u = vel * t - decel * t * t / 2.;
dprintf("can still go: %.5f units\n", u);

		if (u < EPS) break;
		if (d > u) d = u;

dprintf("to go: %.5f\n", d);

		B.x = A.x + d * A.dx;
		B.y = A.y + d * A.dy;

		if ((B.x + 1 * A.dx) < -EPS || (B.x + 1 * A.dx) > (width + EPS))
			B.dx = -A.dx;
		else
			B.dx = A.dx;

		if ((B.y + 1 * A.dy) < -EPS || (B.y + 1 * A.dy) > (height + EPS))
			B.dy = -A.dy;
		else
			B.dy = A.dy;

dprintf("new position (w/o time): (%.5f,%.5f),  new dir: (%.5f,%.5f)\n", B.x, B.y, B.dx, B.dy);

dprintf("distance to Q: %.5f\n", qdist(A, B));
		shortest = fmin(shortest, qdist(A, B));

		A = B;
		if (fabs(d - u) < EPS) break;

		z = posiroot(-decel / 2., vel, -d);
dprintf("time consumed: %.5f\n", z);
		tm += z;
		vel = vel0 - decel * tm;
	}

	return shortest;
}

int main()
{
	int i, j, z[8];
	double ang0, pi;

	pi = 2. * acos(0.);

	for (;;) {
		for (i = j = 0; i < 7 && scanf("%d", &z[i]) == 1; i++)
			j |= z[i];

		if (i < 7 || j == 0)
			break;

		width = z[0];
		height = z[1];
		vel0 = z[2];
		ang0 = z[3] * pi / 180.;
		stop = z[4];
		Q.x = z[5];
		Q.y = z[6];

		S.x = width / 2.;
		S.y = height / 2.;
		S.dx = cos(ang0);
		S.dy = sin(ang0);

dprintf("width=%.0f height=%.0f  S=(%.2f,%.2f) dS=(%.5f,%.5f)   Q=(%.2f,%.2f)\n",
	width, height, S.x, S.y, S.dx, S.dy, Q.x, Q.y);

		printf("%.2f\n", sim());

	}

	return 0;
}
