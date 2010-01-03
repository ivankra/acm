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

struct Reaction { int res, heat; } reaction[8][8];
int N, M, tube[10];
int dp[8][1024];
int INF = 0x1fffffff;

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &M);
		for (int i = 1; i <= M; i++) {
			for (int j = 1; j <= M; j++) {
				scanf("%d %d", &reaction[i][j].res, &reaction[i][j].heat);
			}
		}

		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d", &tube[i]);

		for (int i = 1; i <= M; i++)
			for (int j = 0; j < (1 << N); j++)
				dp[i][j] = INF;

		for (int i = 0; i < N; i++)
			dp[tube[i]][1 << i] = 0;

		for (int mask = 1; mask < (1 << N); mask++) {
			if ((mask & (mask - 1)) == 0) continue;

			for (int left = 0; left != mask; left = (left + (~mask) + 1) & mask) {
				if (left == 0) continue;

				for (int x = 1; x <= M; x++) {
					for (int y = 1; y <= M; y++) {
						int t = dp[x][left] + dp[y][mask ^ left] + reaction[x][y].heat;
						if (t < dp[reaction[x][y].res][mask])
							dp[reaction[x][y].res][mask] = t;
					}
				}
			}
		}

		int best = INF;
		for (int x = 1; x <= M; x++)
			best = min(best, dp[x][(1 << N) - 1]);
		printf("%d\n", best);

		scanf(" / ");
		scanf(" . ");
	}
}
