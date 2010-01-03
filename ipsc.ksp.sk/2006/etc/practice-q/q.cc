#include <cstdio>
#include <cstring>
#include <cassert>

long long rev(long long x) {
	long long y = 0;
	for (; x > 0; x /= 10) y = y * 10 + (x % 10);
	return y;
}

int main()
{
	long long x;
	while (scanf(" %lld %*s", &x) >= 1) {
		int v = 0, w, last = -1;
		for (;;) {
			if (v == 1) break;

			if (v == 2) {
				w = "714"[x%3] - '0';
			} else if (v == 4) {
				w = (rev(x) > x) ? 6 : 2;
			} else if (v == 6) {
				int n = 1, m = 10;
				while (x >= m) { n++; m *= 10; }
				w = ((n & 1) == 0) ? 4 : 7;
			} else if (v == 7) {
				w = "2687077"[((x%7)*(x%7))%7] - '0';
				assert(w != 7);
			} else if (v == 8) {
				w = "99779"[x%5] - '0';
			} else if (v == 9) {
				w = (last == 8) ? 0 : 8;
			} else if (v == 0) {
				int y = (x / 100) % 10;
				w = (y <= 7) ? 7 : 9;
			}

			if (--x <= 0) { x = -1; break; }
			last = v;
			v = w;

			assert(0 <= v && v <= 9);
			assert(v != 3 && v != 5);
		}

		printf("%lld\n", x);
	}
}
