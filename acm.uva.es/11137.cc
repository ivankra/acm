#include <cstdio>
#include <cstring>
#include <cassert>

long long ways[10010];

int main() {
	memset(ways, 0, sizeof(ways));
	ways[0] = 1;

	for (int k = 1; k <= 21; k++) {
		int c = k*k*k;
		for (int v = c; v <= 10000; v++)
			ways[v] += ways[v-c];
	}

	int n;
	while (scanf("%d", &n) == 1 && n!=0/*FIXME*/) {
		assert(1 <= n && n <= 10000);
		printf("%lld\n", ways[n]);
	}
}
