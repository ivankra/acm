#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int m, n;
long long a[512][512], dp[512][512];

long long solve() {
	memset(dp, 0, sizeof(dp));

	for (int i = 1; i <= m; i++)
	for (int j = i; j <= n; j++) {
		dp[i][j] = a[i-1][j-1] + dp[i-1][j-1];
		if (j-1 >= i)
			dp[i][j] >?= dp[i][j-1];
	}

	return dp[m][n];
}

int main() {
	while (scanf("%d %d", &m, &n) == 2) {
		if (m==0 && n==0) break;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				scanf("%lld", &a[i][j]);
		printf("%lld\n", solve());
	}
}
