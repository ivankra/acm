// ICPC Finals 2003 - Problem H - A Spy in the Metro
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int N, appTime, travel[60], dp[256][64];
bool next[256][64], back[256][64];

int solve()
{
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;

	for (int t = 0; t <= appTime; t++) {
		for (int s = 0; s < N; s++) {
			if (dp[t][s] > 1000)
				continue;

			dp[t + 1][s] <?= dp[t][s] + 1;

			if (next[t][s] && t + travel[s] <= appTime)
				dp[t + travel[s]][s + 1] <?= dp[t][s];

			if (back[t][s] && t + travel[s-1] <= appTime)
				dp[t + travel[s-1]][s - 1] <?= dp[t][s];
		}
	}

	return dp[appTime][N-1];
}

int main()
{
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		scanf("%d", &appTime);
		for (int i = 0; i < N-1; i++)
			scanf("%d", &travel[i]);

		memset(next, 0, sizeof(next));
		memset(back, 0, sizeof(back));

		{
			int M1, t;
			scanf("%d", &M1);
			for (int i = 0; i < M1; i++) {
				scanf("%d", &t);
				for (int j = 0; j < N-1 && t <= appTime; j++) {
					next[t][j] = true;
					t += travel[j];
				}
			}
		}

		{
			int M2, t;
			scanf("%d", &M2);
			for (int i = 0; i < M2; i++) {
				scanf("%d", &t);
				for (int j = N-1; j > 0 && t <= appTime; j--) {
					back[t][j] = true;
					t += travel[j-1];
				}
			}
		}

		printf("Case Number %d: ", cs);
		int res = solve();
		if (res < 1000)
			printf("%d\n", res);
		else
			printf("impossible\n");
	}
}
