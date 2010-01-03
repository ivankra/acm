#include <stdio.h>

int main()
{
	static int h, m;
	register int a, b, d;

	while (scanf("%d : %d", &h, &m) == 2 && (h != 0 || m != 0)) {
		while (h >= 12) h -= 12;
		while (m >= 60) m -= 60;

		a = 60 * h + m;
		b = 12 * m;

		if (a >= 720) a %= 720;
		if (b >= 720) b %= 720;

		d = (a >= b) ? (a - b) : (b - a);
		if (d >= 720) d %= 720;
		if (d >= 360) d = 720 - d;

		if (d & 1)
			printf("%d.500\n", d >> 1);
		else
			printf("%d.000\n", d >> 1);
	}

	return 0;
}
