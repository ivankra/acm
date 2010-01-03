#include <stdio.h>

int solve(int n, int m)
{
	int p2, p5, r, t;

	if (m > n)
		return 0;

	for (p2 = p5 = 0, r = 1; m-- > 0 && n > 0; n--) {
		for (t = n; (t & 1) == 0; t >>= 1, p2++);
		for (; (t % 5) == 0; t /= 5, p5++);
		r = (r * t) % 10;
	}

	if (p2 < p5) {
		p5 -= p2;
		p2 = 0;
	} else {
		p2 -= p5;
		p5 = 0;
	}

	while (p2-- > 0)
		r = (r * 2) % 10;

	while (p5-- > 0)
		r = (r * 5) % 10;

	return r;
}

int main()
{
	int n, m;

	while (scanf("%d %d", &n, &m) == 2)
		printf("%d\n", solve(n, m));

	return 0;
}
