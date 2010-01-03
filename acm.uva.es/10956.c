#include <stdio.h>

typedef unsigned long long u64;

static unsigned base, min, max, max2;
static unsigned r_non, r_fails, r_list[50001];

static unsigned modexp(unsigned b, unsigned e, unsigned m)
{
	unsigned r;

	/* assert e > 0 */

	for (r = 1; e > 1; e >>= 1) {
		if (e & 1)
			r = (unsigned)(((u64)r * (u64)b) % m);
		b = (unsigned)(((u64)b * (u64)b) % m);
	}

	r = (unsigned)(((u64)r * (u64)b) % m);
	return r;
}

static int check(unsigned b, unsigned n)
{
	unsigned t, u, x;

	for (u = (n - 1) >> 1, t = 1; (u & 1) == 0; u >>= 1, t++);

	x = modexp(b, u, n);
	if (x == 1 || x == (n - 1)) return 1;

	while (t--) {
		u = ((u64)x * (u64)x) % n;
		if (u == 1)
			return (x == (n - 1)) ? 1 : 0;
		x = u;
	}

	return (x == 1);
}

static void solve()
{
	unsigned x;

	r_non = 0;
	r_fails = 0;

	max2 = max;
	if (max2 > 0 && (max2 & 1) == 0) max2--;

	if (min > max2) return;

	x = min;
	if ((x & 1) == 0) {
		if (min == max2) return;
		x++;
	}
	if (x < 3) x = 3;

	for (;;) {
		if (check(base, x)) {
			if (check(2, x) && check(7, x) && check(61, x)) {
				;
			} else {
				r_non++;
				r_list[r_fails++] = x;
			}
		} else {
			r_non++;
		}


		if (x == max2) break;
		x += 2;
	}
}

int main()
{
	int i, t;

	for (t = 0; scanf("%u %u %u", &base, &min, &max) == 3 && base >= 2; t++) {
		if (t) printf("\n");

		solve();

		printf("There are %u odd non-prime numbers between %u and %u.\n",
			r_non, min, max);
		if (r_fails == 0) {
			printf("There are no failures in base %u.\n", base);
		} else {
			printf("%u suspects fail in base %u:\n", r_fails, base);
			for (i = 0; i < r_fails; i++) printf("%u\n", r_list[i]);
		}
	}

	return 0;
}
