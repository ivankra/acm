#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

const int INF = 0x3fffffff;
int travel[51][51], toll[51][51], N, deadline;
int dp[1001][51];

int main() {
	while (scanf("%d %d", &N, &deadline) == 2 && N > 0) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &travel[i][j]);

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &toll[i][j]);

		for (int t = 0; t <= deadline; t++)
			for (int i = 0; i < N; i++)
				dp[t][i] = INF;
		dp[0][0] = 0;

		int bestToll = INF, bestTime = INF;

		for (int t = 0; t <= deadline; t++) {
			for (int i = 0; i < N; i++) {
				if (dp[t][i] >= INF) continue;

				if (t < deadline)
					dp[t+1][i] = min(dp[t+1][i], dp[t][i]);

				for (int j = 0; j < N; j++) {
					if (t + travel[i][j] <= deadline) {
						int tt = t + travel[i][j];
						dp[tt][j] = min(dp[tt][j], dp[t][i] + toll[i][j]);
					}
				}
			}

			if (dp[t][N-1] < bestToll) {
				bestToll = dp[t][N-1];
				bestTime = t;
			}
		}

		printf("%d %d\n", bestToll, bestTime);
	}
}
