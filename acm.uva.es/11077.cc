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

ull f[32][32];

int main() {
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	for (int n = 1; n <= 30; n++) {
		for (int k = 0; k <= n; k++) {
			f[n][k] = (ull)(n-1) * f[n-1][k] + (ull)f[n-1][k-1];
		}
	}

	int N, K;
	while (scanf("%d %d", &N, &K) == 2 && (N|K) != 0)
		printf("%llu\n", f[N][N-K]);
}
