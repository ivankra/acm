/*
ID: infnty1
LANG: C++
TASK: cheappal
*/
#include <cstdio>
#include <cstring>

int N, M, cost_ins[256], cost_del[256], dp[3][4096];
char tag[5000];

int main() {
	freopen("cheappal.in", "r", stdin);
	freopen("cheappal.out", "w", stdout);

	scanf("%d %d %s", &N, &M, tag);
	for (int i = 0; i < N; i++) {
		char ch;
		scanf(" %c", &ch);
		scanf("%d %d", &cost_ins[ch], &cost_del[ch]);
	}

	memset(dp, 0, sizeof(dp));
	for (int len = 2; len <= M; len++) {
		for (int offs = 0; offs+len <= M; offs++) {
			int res = 1<<30;
			char a = tag[offs], b = tag[offs+len-1];
			if (a == b) {
				res = dp[2][offs+1];
			} else {
				res <?= cost_del[a] + dp[1][offs+1];
				res <?= dp[1][offs] + cost_del[b];
				res <?= cost_ins[b] + dp[1][offs];
				res <?= cost_ins[a] + dp[1][offs+1];
			}
			dp[0][offs] = res;
		}

		for (int i = 0; i <= M; i++) {
			dp[2][i] = dp[1][i];
			dp[1][i] = dp[0][i];
		}
	}

	printf("%d\n", dp[0][0]);
	return 0;
}
