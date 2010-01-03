#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;i++)

int N, val[100], best[65536];

int main() {
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		REP(i,N) scanf("%d", &val[i]);

		best[0] = 0;
		for (int u = 1; u < (1 << N); u++) {
			int i;
			for (i = 0; i < N && (u&(1<<i))==0; i++);
			best[u] = best[u^(1<<i)];

			for (int j = i+1; j < N; j++) if (u & (1 << j))
				for (int k = j+1; k < N; k++) if (u & (1 << k))
					if (val[i]+val[j]+val[k] >= 20)
						best[u] >?= 1 + best[u^(1<<i)^(1<<j)^(1<<k)];
		}

		printf("Case %d: %d\n", cs, best[(1<<N)-1]);
	}
}
