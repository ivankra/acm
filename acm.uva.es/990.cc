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

int main()
{
	int T, N, w;
	int dp[2000], mask[2000], cost[50], value[50];
	for (int cs = 1;scanf("%d %d %d", &T, &w, &N) == 3; cs++) {
		memset(dp, 0, sizeof(dp));
		memset(mask, 0, sizeof(mask));
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &cost[i], &value[i]);
			cost[i] *= 3*w;
			for (int t = T; t >= cost[i]; t--) {
				if (value[i] + dp[t - cost[i]] > dp[t]) {
					dp[t] = value[i] + dp[t - cost[i]];
					mask[t] = mask[t - cost[i]] | (1 << i);
				}
			}
		}

		if (cs != 1) printf("\n");
		printf("%d\n", dp[T]);
		{ int k = 0; for (int z = mask[T]; z != 0; z &= z-1) k++; printf("%d\n", k); }
		for (int i = 0; i < N; i++)
			if (mask[T] & (1 << i)) printf("%d %d\n", cost[i]/(3*w), value[i]);
	}
}
