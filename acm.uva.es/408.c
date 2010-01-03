#include <stdio.h>

static int gcd(int u, int v)
{
	int s;

	for (s = 0; u && v && ((u | v) & 1) == 0; s++)
		u >>= 1, v >>= 1;

	for (;;) {
		if (u == 0) return (v << s);
		if (v == 0) return (u << s);

		while ((u & 1) == 0) u >>= 1;
		while ((v & 1) == 0) v >>= 1;

		if (u > v)
			u = (u - v) >> 1;
		else
			v = (v - u) >> 1;
	}
}

int main()
{
	static int s, m;

	while (scanf("%d %d", &s, &m) == 2)
		printf("%10d%10d    %s Choice\n\n", s, m,
			(gcd(s, m) == 1) ? "Good" : "Bad");

	return 0;
}
