#include <stdio.h>
#include <math.h>

#define EPS 1e-8

struct vec {
	double x, y, z;
	vec(double _x, double _y, double _z) { x = _x; y = _y; z = _z; }
	vec() { }
};

vec operator-(const vec &a, const vec &b) { return vec(a.x - b.x, a.y - b.y, a.z - b.z); }
vec operator+(const vec &a, const vec &b) { return vec(a.x + b.x, a.y + b.y, a.z + b.z); }
double operator*(const vec &a, const vec &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
vec operator*(double c, const vec &v) { return vec(c * v.x, c * v.y, c * v.z); }
double operator^(const vec &a, int n) { return a * a; }

double R;

int f(vec S, vec T)
{
/*
line ST with parameter t in [0,1]: L(t) = (1-t)S + tT
L(0) = S, L(1) = T

R(t) = L(t).L(t) = ((1-t)S + tT).((1-t)S + tT)
                 = (1-t)^2 S.S + 2t(1-t) S.T + t^2 T.T

R'(t) = (2t-2) S.S + (2-4t) S.T + 2t T.T
      = t(2 S.S - 4 S.T + 2 T.T) - 2 S.S + 2 S.T
R'(t) = 0, <==>
      t(2 S.S - 4 S.T + 2 T.T) - 2 S.S + 2 S.T = 0
      t(S.S - 2 S.T + T.T) = S.S - S.T
      t[(S-T).(S-T)] = S.(S - T)
      t = S.(S - T) / [(S-T).(S-T)]
*/
	double t;

	t = (S * (S - T)) / ((S - T)^2);
	if (t < EPS || t > (1. - EPS)) return 1;

	t = sqrt(((1 - t) * S + t * T)^2);
	return (t > (R - EPS));
}

int main()
{
	vec S[128], T[128];
	int i, j, k, m, r;

	R = 10000. / acos(0.);

	while (scanf("%d %d", &k, &m) == 2 && k) {
		for (i = 0; i < k; i++)
			scanf("%lf %lf %lf", &S[i].x, &S[i].y, &S[i].z);

		for (j = 0; j < m; j++)
			scanf("%lf %lf %lf", &T[j].x, &T[j].y, &T[j].z);

		for (j = r = 0; j < m; j++)
			for (i = 0; i < k; i++)
				if (f(S[i], T[j])) { r++; break; }

		printf("%d\n", r);
	}

	return 0;
}
