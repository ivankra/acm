#include <cstdio>

long long sum[1000100], no[50000];
int N;

long long eval(int M) {
	for (int i = 0; i <= M; i++) no[i] = 0;
	no[0] = 1;

	long long res = 0;
	for (int i = 1; i <= N; i++) {
		res += no[sum[i]%M];
		no[sum[i]%M]++;
	}
	return res;
}

int main() {
	int L, U;
	while (scanf("%d %d %d", &N, &L, &U) == 3) {
		sum[0] = 0;
		for (int i = 1; i <= N; i++) {
			long long x;
			scanf("%lld", &x);
			sum[i] = sum[i-1] + x;
		}

		int best_m = L;
		long long best_f = -1;

		for (int m = L; m <= U; m++) {
			long long f = eval(m);
			if (f > best_f) { best_m = m; best_f = f; }
		}
		printf("%d\n", best_m);
	}
}
