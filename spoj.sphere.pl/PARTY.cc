// 0/1 knapsack
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
using namespace std;

int main()
{
	int budget, n;
	int cost[1000], fun[1000], maxFun[1000];

	while (scanf("%d %d", &budget, &n) == 2) {
		if (budget == 0 && n == 0) break;
		
		for (int i = 0; i < n; i++)
			scanf("%d %d", &cost[i], &fun[i]);

		for (int i = 0; i <= budget; i++)
			maxFun[i] = 0;

		for (int i = 0; i < n; i++) {
			for (int c = budget; c >= cost[i]; c--)
				maxFun[c] = max(maxFun[c], maxFun[c-cost[i]] + fun[i]);
		}

		int best = 0, bestFun = 0;
		for (int c = 0; c <= budget; c++)
			if (maxFun[c] > bestFun) bestFun = maxFun[best = c];
		printf("%d %d\n", best, bestFun);
	}
}
