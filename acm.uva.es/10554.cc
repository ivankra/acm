#include <cstdio>

int main() {
	for (;;) {
		int m = 0;
		double a = 0, b = 0;

		for (m = 0;; m++) {
			int i, lhs=100, rhs=0, x[5];
			char c[5];

			for (i = 0; i < 5; i++) {
				if (scanf(" %d %c", &x[i], &c[i]) != 2) break;
				if (c[i] == '%') { lhs -= x[i]; continue; }
				if (c[i] == 'g') x[i] *= "94447"[i] - '0';
				rhs += x[i];
			}
			if (i != 5) break;

			double n = rhs * 100.0 / lhs;
			b += n;
			a += (c[0]=='%' ? x[0]*n/100.0 : x[0]);
		}
		if (m == 0) break;

		scanf(" - ");
		printf("%.0lf%%\n", a/b*100);
	}
}
