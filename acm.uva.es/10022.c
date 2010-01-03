#include <stdio.h>
#include <stdlib.h>

int isqrt(int a)
{
	int x, y;

	for (x = a; x > 1; x = y)
		if ((y = (x + a / x) >> 1) >= x) break;

	return x;
}

int solve(int x1, int x2)
{
	int r1, r2, c1, c2, t, z;

	if (x1 == x2)
		return 0;

	x1--;
	x2--;

	if (x1 > x2) {
		t = x1;
		x1 = x2;
		x2 = t;
	}

	r1 = isqrt(x1);
	r2 = isqrt(x2);

	c1 = x1 - r1 * (r1 + 1);
	c2 = x2 - r2 * (r2 + 1);

	if (r1 == r2)
		return abs(c2 - c1);

	z = 0;
	t = 0;

	if ((abs(c1) & 1) != (r1 & 1))
		t++, z++;

	z += 2 * (r2 - 1 - r1);
	t += (r2 - 1 - r1);

	if ((abs(c2) & 1) == ((r2 - 1) & 1)) {
		z++;
	} else {
		z += 2;
		t++;
	}

	t = abs(c2 - c1) - t;
	if (t > 0)
		z += t;

	return z;
}

int main()
{
	int a, b, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &a, &b) == 2;)
		printf(t ? "%d\n\n" : "%d\n", solve(a, b));

	return 0;
}
