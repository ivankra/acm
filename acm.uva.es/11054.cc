#include <cstdio>

int main() {
	int n;
	while (scanf("%d", &n) == 1 && n > 0) {
		long long x, b = 0, res = 0;
		for (int i = 0; i < n && scanf("%lld", &x) == 1; i++) {
			res += (b > 0 ? b : -b);
			b += x;
		}
		printf("%lld\n", res);
	}
}
