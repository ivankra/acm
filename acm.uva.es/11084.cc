#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;i++)

int ten[100], dig[100], mod, N;
int cs, got[1024][1024], memo[1024][1024];

int f(int k, int used, int sum) {
	if (k == N)
		return sum%mod == 0 ? 1 : 0;

	if (mod-sum < 1024 && got[used][mod-sum] == cs)
		return memo[used][mod-sum];

	int res = 0, z = 0;
	for (int i = 0; i < N; i++) {
		if (used & (1 << i)) continue;
		if (z & (1 << dig[i])) continue;
		z |= 1 << dig[i];
		res += f(k+1, used|(1<<i), (sum + ten[k] * dig[i]) % mod);
	}

	if (mod-sum < 1024) {
		got[used][mod-sum] = cs;
		memo[used][mod-sum] = res;
	}

	return res;
}

int main() {
	int T;
	scanf("%d", &T);

	memset(got, 0, sizeof(got));
	for (cs = 1; cs <= T; cs++) {
		char str[100];
		scanf(" %s %d", str, &mod);
		assert(1 <= mod && mod <= 10000);
		N = strlen(str);
		assert(1 <= N && N <= 10);
		REP(i,N) {
			dig[i] = str[i]-'0';
			assert(0 <= dig[i] && dig[i] <= 9);
		}
		sort(dig, dig+N);

		for (int i = 0; i < 100; i++)
			ten[i] = (i>0 ? 10*ten[i-1] : 1) % mod;

		printf("%d\n", f(0,0,0));
	}
}
