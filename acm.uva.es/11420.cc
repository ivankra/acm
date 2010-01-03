#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long LL;
#define FOREACH(it, v) for(typeof((v).begin())it=(v).begin();it!=(v).end();++it)
#define SIZE(v) ((int)(v).size())
#define ALL(v) (v).begin(), (v).end()
#define REP(i,n) for(int i=0;i<(n);++i)

unsigned long long dp[100][100][2];

int main()
{
	memset(dp, 0, sizeof(dp));
	dp[0][0][1] = 1;
	for (int n = 0; n <= 70; n++) {
		for (int s = 0; s <= n; s++) {
			for (int flag = 0; flag < 2; flag++) {
				dp[n+1][s][0] += dp[n][s][flag];
				if (flag) {
					dp[n+1][s+1][1] += dp[n][s][flag];
				} else {
					dp[n+1][s][1] += dp[n][s][flag];
				}
			}
		}
	}

	int N, S;
	while (scanf("%d %d", &N, &S) == 2) {
		if (N < 0 || S < 0) break;
		printf("%llu\n", dp[N][S][0] + dp[N][S][1]);
	}
}
