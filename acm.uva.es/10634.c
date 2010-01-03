#include <stdio.h>

typedef unsigned long long num;

num gcd(num x, num y) { return (y == 0) ? x : gcd(y, x % y); }

int main()
{
	num v, m, s, r, c, x, y, z;

	while (scanf("%llu %llu", &m, &v) == 2 && v != 0) {
		if ((m & 1) == 0) {
			s = v - 1;
			c = 1;
		} else {
			s = v;
			c = v;
		}
		v--;
		m += v;

		for (r = 0; s <= m;) {
			r += c;

			if ((s + 2) > m) break;

			x = s + 1;
			y = s - v + 1;
			z = gcd(x, y);
			if (z > 1) x /= z, y /= z;
			if (y > 1) c /= y;
			c *= x;
			s++;

			x = s + 1;
			y = s - v + 1;
			z = gcd(x, y);
			if (z > 1) x /= z, y /= z;
			if (y > 1) c /= y;
			c *= x;
			s++;
		}

		printf("%llu\n", r);
	}

	return 0;
}
