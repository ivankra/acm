#include <cstdio>
#include <cstring>
#include <cassert>
#include <gmp.h>
using namespace std;

typedef unsigned long long u64;

unsigned modexp(unsigned b, unsigned e, unsigned m)
{
	unsigned r;
	assert(e > 0);
	for (r = 1; e > 1; e >>= 1) {
		if (e & 1)
			r = (unsigned)(((u64)r * (u64)b) % m);
		b = (unsigned)(((u64)b * (u64)b) % m);
	}
	r = (unsigned)(((u64)r * (u64)b) % m);
	return r;
}

int rbcheck(unsigned b, unsigned n)
{
	unsigned t, u, x;
	for (u = (n - 1) >> 1, t = 1; (u & 1) == 0; u >>= 1, t++);
	x = modexp(b, u, n);
	if (x == 1 || x == (n - 1)) return 1;
	while (t--) {
		u = ((u64)x * (u64)x) % n;
		if (u == 1) return (x == (n - 1)) ? 1 : 0;
		x = u;
	}
	return (x == 1);
}

int isprime(u64 x) {
	if (x <= 2) return (x == 2);
	if ((x & 1) == 0) return 0;
	if (x <= 100) {
		for (int d = 2; d*d <= x; d++)
			if ((x % d) == 0) return 0;
		return 1;
	}
	if (rbcheck(2, x) && rbcheck(7, x) && rbcheck(61, x)) return 1;
	return 0;
}

int main() {
	int T, N, K;
	int a[1010];
	for (scanf("%d", &T); T-- > 0;) {
		scanf("%d %d", &N, &K);
		assert(N < 1000);
		for (int i = 0; i < N; i++) {
			scanf("%d", &a[i]);

	}

}
