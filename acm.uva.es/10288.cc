#include <cstdio>
typedef unsigned long long u64;

u64 gcd(u64 x, u64 y) { return y ? gcd(y, x % y) : x; }
int len(u64 n) { return n > 9 ? 1 + len(n/10) : 1; }

int main(int n) {
	while (scanf("%d", &n) == 1) {
		u64 p = 0, q = 1, r;
		for (int k = 1; k <= n; k++) {
			p = p * k + q * n;
			q *= k;
			r = gcd(p, q); p /= r; q /= r;
		}

		if (q == 1) {
			printf("%llu\n", p);
		} else {
			printf("%*s %llu\n", len(p/q), "", p % q);
			printf("%llu %.*s\n", p/q, len(q), "--------------------");
			printf("%*s %llu\n", len(p/q), "", q);
		}
	}
	return 0;
}
