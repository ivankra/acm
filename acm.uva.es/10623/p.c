#include <stdio.h>
#include <stdlib.h>

typedef struct { int x, y, z; } triple_t;

int cmp(const void *p, const void *q)
{
	triple_t *a = (triple_t *)p, *b = (triple_t *)q;
	if (a->x != b->x) return (a->x - b->x);
	return (a->y != b->y) ? (a->y - b->y) : (a->z - b->z);
}

int f(int e, int c, int t)
{
	int r = (c == 0) ? 1 : (c * c - c + 2);
	if (e > 0) r += (2 * c + e - 1) * e * 2 + ((r == 1) ? 1 : 0);
	if (t > 0) r += (2 * (c + e) + t - 1) * t * 3 + ((r == 1) ? 1 : 0);
	return r;
}

int solve(int x)
{
	static triple_t sol[16384];
	int a, b, c, d, e, t, n;

	for (n = 0, t = 0; t < 100; t++) {
		if (f(0, 0, t) > x) break;
		for (e = 0; e < 100; e++) {
			if (f(e, 0, t) > x) break;

			for (a = 0, b = 19999; a <= b;) {
				d = f(e, c = (a + b) >> 1, t);
				if (d > x)
					b = c - 1;
				else if (d < x)
					a = c + 1;
				else
					break;
			}

			if (a <= b)
				sol[n].x = e, sol[n].y = c, sol[n].z = t, n++;
		}
	}

	if (n < 1)
		return 1;

	qsort(sol, n, sizeof(sol[0]), &cmp);

	for (c = 0; c < n; c++)
		printf("%d %d %d\n", sol[c].x, sol[c].y, sol[c].z);

	return 0;
}

int main()
{
	int t;
	long long x;

	for (t = 1; scanf("%lld", &x) == 1 && x >= 0; t++) {
		printf("Case %d:\n", t);
		if (x > 420089502 || solve(x))
			printf("Impossible.\n");
	}

	return 0;
}
