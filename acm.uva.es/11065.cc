#include <cstdio>
#include <cstring>
typedef unsigned long long u64;

u64 adj[64], adja[64], all;
int N, resN, resMax;

void go(int k, int in, u64 cov) {
	for (;; k++) {
		if ((cov | adja[k]) != all) return;

		if (cov == all) {
			resN++;
			resMax >?= in;
			return;
		}

		if (k >= N) return;

		if ((cov & (1LL << k)) == 0)
			go(k+1, in+1, cov|adj[k]);
	}
}

int main() {
	int T, M, x, y;
	scanf("%d", &T);
	while (T-- > 0 && scanf("%d %d", &N, &M) == 2 && N > 0) {
		memset(adj, 0, sizeof(adj));
		while (M-- > 0 && scanf("%d %d", &x, &y) == 2) {
			adj[x] |= 1LL << y;
			adj[y] |= 1LL << x;
		}
		for (int i = 0; i < N; i++) adj[i] |= 1LL << i;

		adja[N] = 0;
		for (int i = N-1; i >= 0; i--) adja[i] = adj[i] | adja[i+1];

		all = (1LL << N) - 1;

		resN = resMax = 0;
		go(0, 0, 0);

		printf("%d\n%d\n", resN, resMax);
	}
}
