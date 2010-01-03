#include <stdio.h>
#include <stdlib.h>

long long int_sqrt(long long n)
{
	register long long x, y;

	for (x = n; x > 0; x = y) {
		y = (x + (n / x)) >> 1;
		if (y >= x)
			return x;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	long long x, y, l, s;
	long long m;

	m = (argc > 1) ? atoi(argv[1]) : 1;

	printf("%d x^2 + %d x = y^2\n", (int)m, (int)m);

	for (x = 0; x < 10000000; x++) {
		l = m * ((x * (x + 1)) >> 1);

		s = int_sqrt(l);
		if ((s * s) != l)
			continue;

		printf("x=%-10d y=%d\n", (int)x, (int)s);
		fflush(stdout);
	}

	return 0;
}
