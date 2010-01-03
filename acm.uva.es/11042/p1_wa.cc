#include <cstdio>
#include <algorithm>
using namespace std;

unsigned long long xabs(long long x) { return x < 0 ? -x : x; }

struct Complex {
	long long a, b;
	unsigned long long abs2() { return xabs(a)*xabs(a)+xabs(b)*xabs(b); }
};

Complex mul(const Complex &x, const Complex &y) {
	Complex r = { x.a*y.a-x.b*y.b, x.a*y.b+x.b*y.a };
	return r;
}

int main() {
	int T;
	Complex c, t;
	for (scanf("%d", &T); T-- > 0 && scanf("%lld %lld", &c.a, &c.b) == 2;) {
		if (c.b == 0) { printf("1\n"); continue; }

		t = c;
		for (int N = 1; N <= 70; N++) {
			if (t.b == 0) { printf("%d\n", N); goto done; }
			t = mul(t, c);
			if (t.abs2() >= (1LL << 60)) break;
		}

		printf("TOO COMPLICATED\n");
done:;
	}
}
