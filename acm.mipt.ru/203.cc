#include <cstdio>
#include <cstring>
#include <cassert>
typedef unsigned long long u64;

struct Big {
	int n;
	unsigned a[63];

	void operator =(int x) { a[0]=x; n=x?1:0; }

	void operator +=(const Big &y) {
		unsigned c = 0;
		int i;
		while (n < y.n) a[n++] = 0;
		for (i = 0; i < y.n; i++, c >>= 31)
			a[i] = (c += a[i] + y.a[i]) & 0x7fffffff;
		for (; i < n && c > 0; i++, c >>= 31)
			a[i] = (c += a[i]) & 0x7fffffff;
		if (c > 0) a[n++] = c;
	}

	void operator -=(const Big &y) {
		unsigned c = 1;
		int i;
		while (n < y.n) a[n++] = 0;
		for (i = 0; i < y.n; i++, c >>= 31)
			a[i] = (c += a[i] + (0x7fffffff ^ y.a[i])) & 0x7fffffff;
		for (; i < n; i++, c >>= 31)
			a[i] = (c += a[i] + 0x7fffffff) & 0x7fffffff;
		while (n > 0 && a[n-1] == 0) n--;
	}

	void addsq(const Big &y) {
		while (n < 2*y.n+4) a[n++] = 0;
		for (int i = 0; i < y.n; i++) {
			u64 c = 0;
			int j = 0, k = i;
			for (; j < y.n; j++, k++, c >>= 31)
				a[k] = (c += a[k] + y.a[i]*(u64)y.a[j]) & 0x7fffffff;
			for (; c > 0; k++, c >>= 31)
				a[k] = (c += a[k]) & 0x7fffffff;
		}
		while (n > 0 && a[n-1] == 0) n--;
	}

	void print() {
		char s[1024], *p=s+sizeof(s)-3; *--p = 0;
		while (n > 0) {
			u64 r = 0;
			for (int i = n-1; i >= 0; i--) {
				r = (r << 31) | (u64)a[i];
				a[i] = r / 10;
				r %= 10;
			}
                        *--p = '0' + (int)r;
			while (n > 0 && a[n-1] == 0) n--;
		}
		printf("%s\n", *p ? p : "0");
	}
};

int N, Q;
Big f[3010];

int main()
{
	scanf("%d %d", &N, &Q);

	memset(f, 0, sizeof(f));
	f[0] = 1;

	int ms = N * (Q - 1);
	for (int n = 1; n <= N; n++) {
		Big t; t = 0;
		for (int d = 0; d < Q-1; d++) t += f[ms-d];

		for (int s = ms; s >= 1; s--) {
			if (s-(Q-1) >= 0) t += f[s-(Q-1)];
			t -= f[s];
			f[s] += t;
		}
	}

	Big res; res = 0;
	for (int s = 0; s <= ms; s++)
		res.addsq(f[s]);
	res.print();
}
