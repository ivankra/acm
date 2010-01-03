#include <stdio.h>

int main()
{
	static int fib[2][4], cof[2][4], a, b, m, n, t;
	int i, *fc, *fn, *cc, *cn;

	scanf("%d", &t);

	while (t-- > 0) {
		if (scanf("%d %d %d %d", &a, &b, &n, &m) < 4)
			break;

		fc = fib[0];
		fn = fib[1];
		cc = cof[0];
		cn = cof[1];

		fc[0] = fc[3] = 1; fc[1] = fc[2] = 0;
		cc[0] = cc[1] = cc[2] = 1; cc[3] = 0;

		for (i = n; i > 0; i >>= 1) {
			if (i & 1) {
				fn[0] = (fc[0] * cc[0] + fc[1] * cc[2]) % 10000;
				fn[1] = (fc[0] * cc[1] + fc[1] * cc[3]) % 10000;
				fn[2] = (fc[2] * cc[0] + fc[3] * cc[2]) % 10000;
				fn[3] = (fc[2] * cc[1] + fc[3] * cc[3]) % 10000;
				fc = fn;
				fn = (fn == fib[0]) ? fib[1] : fib[0];
			}

			if (i > 1) {
				cn[0] = (cc[1] * cc[2] + cc[0] * cc[0]) % 10000;
				cn[3] = (cc[1] * cc[2] + cc[3] * cc[3]) % 10000;
				cn[1] = (cc[1] * (cc[0] + cc[3])) % 10000;
				cn[2] = (cc[2] * (cc[0] + cc[3])) % 10000;
				cc = cn;
				cn = (cn == cof[0]) ? cof[1] : cof[0];
			}
		}

		for (i = 1; m-- > 0;)
			i *= 10;
		i = (a * fc[3] + b * fc[1]) % i;
		printf("%d\n", i);
	}

	return 0;
}
