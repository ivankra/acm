#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;i++)

int v[100010], cnt[1000], M;

int mod(int x) {
	if (x < 0) x = M - ((-x) % M);
	return x % M;
}

int main() {
	int N, T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &N, &M);

		REP(i, N) scanf("%d", &v[i]);
		sort(v, v+N);

		long long res = 0, res1 = 0;

		REP(i,M+1) cnt[i]=0;

		v[N] = v[N-1]+1;
		for (int i = 0; i < N;) {
			if (v[i] == v[i+1] && mod(v[i]+v[i]) == 0) res1++;
			while (v[i] == v[i+1]) i++;
			cnt[mod(v[i++])]++;
		}

		for (int x = 0; x <= M; x++) {
			res += cnt[x] * (long long)cnt[mod(M-x)];
			if (mod(x+x) == 0) res -= cnt[x];
		}

		printf("Case %d: %lld\n", cs, res/2+res1);
	}
}
