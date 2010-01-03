#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;i++)
typedef unsigned long long ull;

int a[20], cnt[20], N;
ull fact[20];

int main() {
	fact[0] = 1;
	for (int i = 1; i < 20; i++) fact[i] = fact[i-1] * (ull)i;

	while (scanf("%d", &N) == 1 && N > 0) {
		memset(cnt, 0, sizeof(cnt));
		REP(i,N) { scanf("%d", &a[i]); cnt[a[i]]++; }

		ull e = 1;
		REP(i,N-1) e = e * 10ULL + 1;

		ull res = 0;
		REP(i,N) res += a[i] * fact[N-1];

		for (int i = 0; i <= 9; i++)
			res /= (ull)fact[cnt[i]];
		printf("%llu\n", res*e);
	}
}
