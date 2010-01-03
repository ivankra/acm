#include <stdio.h>
#include <math.h>

int testcase(int s, int m, int c)
{
	register int i;
	for (i = 0; i < s; i++) {
		if (((c -= m) % s) != 0) return 0;
		c -= (c / s);
	}
	return ((c % s) == 0);
}

int main()
{
	int i, t, s, m, l, h;
	register int k, n, x, v;

	scanf("%d", &t);
	for (i = 0; i < t; i++) {
		scanf("%d %d %d %d", &s, &m, &l, &h);

		for (k = 0, n = 0; ; ) {
			for (x = k*s, v = 0; v <= s; v++) {
				x *= s;
				if ((x % (s - 1)) != 0)
					break;
				x /= (s - 1);
				x += m;
			}
			if (x > h)
				break;
			if (v >= s && x >= l)
				n++;
			k++;


		}

		printf("%d\n", n);
	}

	return 0;
}
