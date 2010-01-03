#include <stdio.h>
#include <stdlib.h>

#define INF 0xFFFFFFFU

typedef unsigned long long u64;

unsigned modexp(unsigned b, unsigned e, unsigned m) {
	unsigned r;
	for (r = 1; e > 0; e >>= 1) {
		if (e & 1) r = (unsigned)(((u64)r * (u64)b) % (u64)m);
		b = (unsigned)(((u64)b * (u64)b) % (u64)m);
	}
	return r;
}

unsigned modmul(unsigned a, unsigned b, unsigned m) {
	return (unsigned)(((u64)a * (u64)b) % (u64)m);
}

int cmp(const void *p, const void *q) {
	unsigned x = *(unsigned *)p, y = *(unsigned *)q;
	return (x > y) ? 1 : ((x < y) ? -1 : 0);
}

unsigned isqrt(unsigned a) {
	unsigned x, y;
	for (x = a; x > 1; x = y)
		if ((y = (x + a / x) >> 1) >= x) break;
	return x;
}

int look(unsigned s[], int b, unsigned x) {
	int a, c;
	for (a = 0, b--; a <= b;) {
		if (s[c = (a + b) >> 1] < x)
			a = c + 1;
		else if (s[c] > x)
			b = c - 1;
		else
			return 1;
	}
	return 0;
}

unsigned solve(unsigned a, unsigned b, unsigned m) {
	static unsigned s[65536];
	unsigned i, k, n, y;

	a %= m;
	b %= m;

	n = isqrt(m);
	if (n * n < m) n++;

	if (b == 1) return 0;

/* a^x = b (mod m)
   x = ny-z, n=ceil(sqrt(m)), 1<=y<=n, 0<=z<n.
   (a^n)^y = b a^z (mod m)
*/
	for (s[0] = b, i = 1; i < n; i++)
		s[i] = modmul(s[i-1], a, m);
	qsort(s, n, sizeof(s[0]), &cmp);

	k = modexp(a, n, m);
	for (y = 1, i = 1; y <= n; y++) {
		i = modmul(i, k, m);
		if (look(s, n, i)) break;
	}

	if (y > n) return INF;

	y = n * (y - 1);
	k = modexp(a, y, m);

	while (k != b) {
		k = modmul(k, a, m);
		y++;
	}

	return y;
}

int main() {
	unsigned a, b, m, r;
	while (scanf("%u %u %u", &m, &a, &b) == 3) {
		if ((r = solve(a, b, m)) == INF)
			printf("no solution\n");
		else
			printf("%u\n", r);
	}
	return 0;
}
