#include <cstdio>
#include <cstring>
#include <cassert>

struct big {
	unsigned long long a[2];
	big() { a[0] = a[1] = 0; }
	void operator =(const char *s) {
		while (*s) {
			a[0] = a[0] * 10 + *s++ - '0';
			a[1] = a[1] * 10 + (a[0] >> 55);
			a[0] &= (1ULL << 55) - 1;
		}
	}
	bool is_zero() { return a[0]==0 && a[1]==0; }
	int get(int k) { return (a[k/55] >> (k%55)) & 1; }
	void clr(int k) { a[k/55] &= ~(1ULL << (k%55)); }
	void dec() { if (a[0] != 0) a[0]--; else { a[0]=(1ULL<<55)-1; a[1]--; } }
	void inc() { a[0]++; a[1] += (a[0] >> 55); a[0] &= (1ULL<<55)-1; }
};

int peg[3];

void doit(int n, int S, int M, int T, big m) {
	if (m.is_zero() || n <= 0) return;

	m.inc();
	if (m.get(n)) { peg[S] -= n; peg[T] += n; return; }

	if (m.get(n-1) == 0) {
		m.dec();
		doit(n-1, S, T, M, m);
		return;
	}

	m.clr(n-1); peg[S] -= n-1; peg[M] += n-1;

	if (m.is_zero()) return;
	m.dec(); peg[S]--; peg[T]++;

	if (m.is_zero()) return;
	doit(n-1, M, S, T, m);
}

int main() {
	int n;
	char s[1000];
	while (scanf(" %d %[0-9]", &n, s) == 2 && n > 0) {
		assert(1 <= n && n <= 100);

		big m; m = s;

		peg[0] = n;
		peg[1] = 0;
		peg[2] = 0;
		doit(n, 0, 1, 2, m);

		if (n & 1)
                	printf("%d %d %d\n", peg[0], peg[2], peg[1]);
		else
                	printf("%d %d %d\n", peg[0], peg[1], peg[2]);
	}
}
