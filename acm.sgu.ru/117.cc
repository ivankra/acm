#include <cstdio>

int modexp(int a, int b, int m) {
	int r = 1;
	for (; b > 0; b >>= 1) {
		if (b & 1) r = (r * a) % m;
		a = (a * a) % m;
	}
	return r;
}

int main() {
	int n, m, k, x, res=0;
	scanf("%d %d %d", &n, &m, &k);
	while (n-- > 0 && scanf("%d", &x) == 1)
		if (modexp(x, m, k) == 0) res++;
	printf("%d\n", res);
}
