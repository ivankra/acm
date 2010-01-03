// DP, knapsack
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

int INF = 0x1fffffff;
int N, W, Cw[1000], Cp[1000];
int dp[10010];

void solve()
{
	dp[0] = 0;
	for (int w = 1; w <= W; w++) {
		dp[w] = INF;
		for (int i = 0; i < N; i++)
			if (Cw[i] <= w)
				dp[w] = min(dp[w], Cp[i] + dp[w - Cw[i]]);
	}

	if (dp[W] >= INF)
		printf("This is impossible.\n");
	else
		printf("The minimum amount of money in the piggy-bank is %d.\n", dp[W]);
}

int main()
{
	int T, E, F;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d", &E, &F, &N);
		W = F - E;
		for (int i = 0; i < N; i++)
			scanf("%d %d", &Cp[i], &Cw[i]);
		solve();
	}
}
