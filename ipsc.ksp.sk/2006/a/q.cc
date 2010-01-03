#include <cstdio>
#include <cassert>

int main() {
	int T, N;
	char str[1024];
	for (scanf("%d", &T); T-- > 0 && scanf("%d", &N) == 1;) {
		long long sum = 0, a;
		for (int i = 0; i < N && scanf(" %s", str) == 1; i++) {
			a = 0;
			for (int j = 0; str[j]; j++)
				a = (a * 10LL + str[j] - '0') % N;
			sum = (sum + a) % N;
		}
		printf((sum%N)==0 ? "YES\n" : "NO\n");
	}
}
