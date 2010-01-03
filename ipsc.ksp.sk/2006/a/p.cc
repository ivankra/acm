#include <cstdio>
#include <cassert>

int main() {
	int T, N;
	for (scanf("%d", &T); T-- > 0 && scanf("%d", &N) == 1;) {
		long long sum = 0, a;
		for (int i = 0; i < N && scanf(" %lld", &a) == 1; i++) {
			assert(sum+a >= sum);
			sum += a;
		}

		fprintf(stderr, "sum=%lld\n", sum);

		printf((sum%N)==0 ? "YES\n" : "NO\n");
	}
}
