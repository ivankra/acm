#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

struct Big {
	int n;
	unsigned a[15];

	Big() { n = 0; }

	void operator =(int x) { n = x ? 1 : 0; a[0] = x; }
	void operator =(const Big &x) { memcpy(a, x.a, (n=x.n)*sizeof(unsigned)); }

	void shl() {
		if (n > 0) {
			assert(n <= 15);
			if (a[n-1] >> 15) a[n++] = 0;
			for (int i = n-1; i > 0; i--)
				a[i] = ((a[i] << 1) | (a[i-1] >> 15)) & 0xffff;
			a[0] = (a[0] << 1) & 0xffff;
			while (n > 0 && a[n-1] == 0) n--;
		}
	}

	void add2(int k) {
		while (n < k/16+1) {
			assert(n <= 15);
			a[n++] = 0;
		}

		unsigned c = 1U << (k % 16);
		for (int i = k/16; i < n; i++, c >>= 16)
			a[i] = (c += a[i]) & 0xffff;
		if (c) a[n++] = c;

		while (n > 0 && a[n-1] == 0) n--;
	}

	void dec() {
		for (int i = 0; i < n; i++) {
			if (a[i] > 0) { a[i]--; break; }
			a[i] = 0xffff;
		}
		while (n > 0 && a[n-1] == 0) n--;
	}

	bool operator <(const Big &x) const {
		if (n != x.n) return n < x.n;
		for (int i = n-1; i >= 0; i--)
			if (a[i] != x.a[i]) return a[i] < x.a[i];
		return false;
	}

	void print() {
		if (n <= 0) { printf("0\n"); return; }

		static char buf[65536];
		char *p = buf+sizeof(buf)-2; *--p = 0;
		Big x = *this;

		while (x.n > 0) {
			unsigned r = 0;
			for (int i = x.n-1; i >= 0; i--) {
				r = (r << 16) | x.a[i];
				x.a[i] = r / 10;
				r %= 10;
			}
                        *--p = r + '0';
                        while (x.n > 0 && x.a[x.n-1] == 0) x.n--;
		}
		printf("%s\n", p);
	}
};

int main() {
	Big a[10001], t;
	int n;

	a[0] = 0; a[1] = 1;
	for (n = 2; n <= 10000; n++) {
		a[n].n = 1<<20;
		for (int k = n-1; k > 0; k--) {
			if (n-k > a[n].n*16+10) break;
			t = a[k]; t.shl(); t.add2(n-k); t.dec();
			if (a[n].n == 1<<20 || t < a[n])
				a[n] = t;
		}
	}

	while (scanf("%d", &n) == 1)
		a[n].print();
}
