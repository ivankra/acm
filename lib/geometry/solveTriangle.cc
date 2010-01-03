/* UVa 194.  Given measures of some angles and sides of a triangle, determine
   measures of everything else. */
#include <cstdio>
#include <cassert>
#include <cmath>
typedef long double real;

real ab(real x) { return (x < 0.0L) ? -x : x; }
real sq(real x) { return x*x; }

struct Triangle {
	real a[3];    /* angles (in radians) */
	real s[3];    /* s[i] = length of side, opposite to angle a[i]. */
};

/*
 *  Unknown parts should be marked by -1 in the input.
 *
 *  Assumes that in a valid triangle all sides and angles are strictly greater
 *  than zero.
 *
 *  Returns:
 *    -1 = infinitely many solutions
 *    0 = no solutions (invalid or inconsistent input)
 *    1 = unique solution (returned)
 *    2+ = number of solutions, if finite.
 */
int solve(Triangle &T) {
	real pi = 2*acos(0.0L), eps = 1e-12L, input_eps = 1e-7L;
	int x1=-1, x2;

	for (int i = 0; i < 3; i++) {
		if (ab(T.a[i]) < eps || T.a[i] > pi-eps) return 0;
		if (ab(T.s[i]) < eps) return 0;
	}

again:
	/* alpha + beta + gamma = pi */
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
	for (int k = 0; k < 3; k++) {
		if (i == j || i == k || j == k) continue;
		if (T.a[i] < eps || T.a[j] < eps) continue;

		real c = pi - T.a[i] - T.a[j];
		if (c < eps || c > pi-eps) return 0;

		if (T.a[k] < eps)
			T.a[k] = c;
		else if (ab(c - T.a[k]) > input_eps)
			return 0;
	}

	/* law of cosines: c^2 = a^2 + b^2 - 2ab cos(C) */
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
	for (int k = 0; k < 3; k++) {
		if (i == j || i == k || j == k) continue;
		if (T.s[i] < eps || T.s[j] < eps || T.a[k] < eps) continue;

		real c = sq(T.s[i]) + sq(T.s[j]) - 2.0L * T.s[i] * T.s[j] * cos(T.a[k]);
		if (c < eps) return 0;

		c = sqrt(c);
		if (T.s[k] < eps)
			T.s[k] = c;
		else if (ab(T.s[k]-c) > input_eps)
			return 0;
	}

	/* law of cosines: cos(C) = (a^2 + b^2 - c^2) / (2ab) */
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
	for (int k = 0; k < 3; k++) {
		if (i == j || i == k || j == k) continue;
		if (T.s[i] < eps || T.s[j] < eps || T.s[k] < eps) continue;

		real c = sq(T.s[i]) + sq(T.s[j]) - sq(T.s[k]);
		c /= 2.0L * T.s[i] * T.s[j];
		if (c > 1.0L-eps || c < -1.0L+eps) return 0;

		c = acos(c);
		if (c < eps || c > pi-eps) return 0;

		if (T.a[k] < eps)
			T.a[k] = c;
		else if (ab(T.a[k]-c) > input_eps)
			return 0;
	}

	/* law of sines: a = b sin(A)/sin(B) */
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++) {
		if (i == j) continue;
		if (T.s[j] < eps || T.a[i] < eps || T.a[j] < eps) continue;

		real c = T.s[j] * sin(T.a[i]) / sin(T.a[j]);
		if (c < eps) return 0;

		if (T.s[i] < eps)
			T.s[i] = c;
		else if (ab(T.s[i]-c) > input_eps)
			return 0;
	}

	/* law of sines: sin(A) = sin(B) a/b */
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++) {
		if (i == j) continue;
		if (T.s[i] < eps || T.s[j] < eps || T.a[j] < eps) continue;

		real c = sin(T.a[j]) * T.s[i] / T.s[j];
		if (c > 1.0L-eps || c < eps) return 0;

		real a1 = asin(c);
		real a2 = pi - a1;

		if (a1 < eps) return 0;

		if (T.a[i] > eps) {
			if (ab(T.a[i] - a1) < input_eps) continue;
			if (ab(T.a[i] - a2) < input_eps) continue;
			return 0;
		}

		if (ab(a1 - a2) < eps) {
			T.a[i] = pi/2;
			continue;
		}

		Triangle T1 = T, T2 = T;
		T1.a[i] = a1;
		T2.a[i] = a2;
		int n1 = solve(T1), n2 = solve(T2);

		if (n1 < 0 || n2 < 0) return -1;
		if (n1 + n2 != 1) return n1 + n2;

		T = (n1 == 1) ? T1 : T2;
	}

	x2 = 0;
	for (int i = 0; i < 3; i++) {
		x2 = (x2 << 1) | (T.a[i] < eps ? 1 : 0);
		x2 = (x2 << 1) | (T.s[i] < eps ? 1 : 0);
	}

	if (x1 != x2) {
		x1 = x2;
		goto again;
	}

	for (int i = 0; i < 3; i++)
		if (T.a[i] < eps || T.s[i] < eps) return -1;
	return 1;
}

int main()
{
	int T;
	Triangle z;
	for (scanf("%d", &T); T-- > 0;) {
		for (int i = 0; i < 3; i++) {
			int x = scanf(" %Lf %Lf", &z.s[i], &z.a[i]);
			assert(x == 2);
		}

		int c = solve(z);
		if (c <= 0) {
			printf("Invalid input.\n");
		} else if (c == 1) {
			for (int i = 0; i < 3; i++)
				printf("%.12Lf %.12Lf%s", z.s[i], z.a[i], i < 2 ? " " : "\n");
		} else {
			printf("More than one solution.\n");
		}
	}
	return 0;
}
