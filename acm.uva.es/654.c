#include <stdio.h>
#include <math.h>

typedef struct { int p, q; } ratio;

int closer(ratio a, ratio b, ratio c)
{
	long long r1, r2;

	r1 = (long long)(a.p * b.q - a.q * b.p) * (long long)c.q;
	if (r1 < 0) r1 = -r1;

	r2 = (long long)(b.p * c.q - c.p * b.q) * (long long)a.q;
	if (r2 < 0) r2 = -r2;

	if (r1 < r2)
		return 1;
	else if (r1 == r2)
		return 0;
	else
		return -1;
}

int main()
{
	ratio r, a, p;
	int t;

	for (t = 0; scanf("%d %d", &r.p, &r.q) == 2; t++) {
		if (t != 0) printf("\n");

		for (a.q = 1; a.q <= r.q; a.q++) {
			a.p = (r.p * a.q + (r.q >> 1)) / r.q;

			if (a.q == 1 || closer(a, r, p) > 0) {
				printf("%d/%d\n", a.p, a.q);
				p = a;
			}
		}
	}

	return 0;
}
