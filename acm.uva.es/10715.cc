#include <cstdio>
#include <cstring>
#include <cstdlib>

#define SCALE 10000

char dp[101][SCALE+1], act[101][SCALE+1];

int main()
{
	int N, p[101];
	while (scanf("%d", &N) == 1 && N > 0) {
		double w[101], sum = 0;
		for (int i = 1; i <= N; i++) {
			scanf("%lf", &w[i]);
			sum += w[i];
		}

		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		for (int i = 1; i <= N; i++) {
			p[i] = (int)(w[i] / sum * SCALE + 0.5);
			if (p[i] < 0) p[i] = 0;
			if (p[i] > SCALE) p[i] = SCALE;

			for (int s = 0; s <= SCALE; s++) {
				dp[i][s] = dp[i-1][s];
				act[i][s] = 0;
			}

			for (int s = p[i]; s <= SCALE; s++) {
				if (dp[i-1][s-p[i]]) {
					dp[i][s] = 1;
					act[i][s] = 1;
				}
			}
		}

		int s = 0;
		for (int i = 0; i <= SCALE; i++) {
			if (dp[N][i] && abs(SCALE-i - i) <= abs(SCALE-s - s)) s = i;
		}

		int res[1000], k = 0;
		for (int n = N; n >= 1; n--) {
			if (act[n][s] == 1) {
				res[k++] = n;
				s -= p[n];
			}
		}

		while (k > 0) {
			k--;
			printf(k == 0 ? "%d" : "%d ", res[k]);
		}
		printf("\n");
	}
}
