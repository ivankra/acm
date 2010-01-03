#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

#define MAX 500000

int coin[100], N;
int greedy[MAX], dp[MAX];

int main()
{
	freopen("change.in", "r", stdin);
	freopen("change.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &coin[i]);
	sort(coin, coin+N);

	dp[0] = 0;
	greedy[0] = 0;

	int i, s;
	for (s = 1; s < MAX; s++) {
		dp[s] = dp[s - 1] + 1;
		for (i = 0; i < N && coin[i] <= s; i++)
			dp[s] = min(dp[s], dp[s - coin[i]] + 1);

		greedy[s] = 1 + greedy[s - coin[i - 1]];

		if (dp[s] != greedy[s]) {
			printf("%d %d\n", s, dp[s]);
			return 0;
		}
	}

	printf("-1 -1\n");
	return 0;
}
