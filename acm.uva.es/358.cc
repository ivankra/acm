#include <cstdio>
#include <cmath>

double cut(double R, double r) {
	double a = acos(1 - r*r/(2*R*R));
	double b = acos(r/(2*R));
	return (a-sin(a))*R*R + b*r*r;
}

int main() {
	int T;
	double R, P;
	for (scanf("%d", &T); T-- > 0 && scanf(" %lf %lf", &R, &P) == 2;) {
		double left = 0, right = 2*R, area = 3.14159*R*R;
		while (right - left > 1e-9) {
			double r = (left + right) / 2;
			if (cut(R, r) > P * area)
				right = r;
			else
				left = r;
		}
		printf("R = %.0f, P = %.2f, Rope = %.2f\n",
			R, P, (left + right) / 2);
		if (T) printf("\n");
	}
}
