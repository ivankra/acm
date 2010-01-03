#include <stdio.h>

int main()
{
	long long m, n, lm, ln, rm, rn, cm, cn;

	while (scanf("%lld %lld", &m, &n) == 2 && (m != 1 || n != 1)) {
		lm = 0; ln = 1;
		rm = 1; rn = 0;

		for (;;) {
			cm = lm + rm;
			cn = ln + rn;

			if (cm == m && cn == n)
				break;

			if ((m * cn) < (n * cm)) {
				putchar('L');
				rm = cm;
				rn = cn;
			} else {
				putchar('R');
				lm = cm;
				ln = cn;
			}
		}

		putchar('\n');
	}

	return 0;
}
