#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;++i)

unsigned long long f[32][32][2];

int main() {
	memset(f, 0, sizeof(f));

	REP(n, 30) REP(k, n+1) REP(p, 2) {
		unsigned long long &res = f[n][k][p];
		if (n == 0) { res = 1; continue; }

		// we have n players, split into two parts:
		// A={1,2,...,k} and B={k+1,...,n}.
		// If p==0, the first player in the line must be chosen from A,
		// otherwise it must be a player from B.

		for (int i = 0; i < n; i++) {
			if (p == 0 && i >= k) continue;
			if (p == 1 && i < k) continue;
			res += f[n-1][i][1-p];
		}
	}

	int n, s;
	while (scanf("%d %d", &n, &s) == 2) {
		assert(1 <= n && n <= 22 && 1 <= s && s <= n);

		if (n <= 2) { printf("1\n"); continue; }

		if (s == 1)
			printf("%llu\n", f[n-2][1][0]);
		else
			printf("%llu\n", f[n-1][s-1][0]);
	}
}
