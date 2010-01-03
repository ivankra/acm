#include <cstdio>
#include <cstring>

int cost[3][32];
int adj[3][32][32];
int N, M, K;

int main()
{
	while (scanf("%d %d %d", &N, &M, &K) == 3) {
		memset(adj, 0, sizeof(adj));

		for (int i = 0; i < N; i++) {
			scanf("%d", &cost[0][i]);
			for (int j = 0; j < M; j++)
				scanf("%d", &adj[0][i][j]);
		}

		for (int i = 0; i < M; i++) {
			scanf("%d", &cost[1][i]);
			for (int j = 0; j < K; j++)
				scanf("%d", &adj[1][i][j]);
		}

		for (int i = 0; i < K; i++) {
			scanf("%d", &cost[2][i]);
			for (int j = 0; j < N; j++)
				scanf("%d", &adj[2][i][j]);
		}

		int bestCost = 0x7fffffff;
		int best[3]={-1,-1,-1};

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				for (int k = 0; k < K; k++) {
					int c = cost[0][i] + cost[1][j] + cost[2][k];
					if (c >= bestCost) continue;

					if (adj[0][i][j]) continue;
					if (adj[1][j][k]) continue;
					if (adj[2][k][i]) continue;

					bestCost = c;
					best[0] = i;
					best[1] = j;
					best[2] = k;
				}
			}
		}

		if (best[0] < 0) {
			printf("Don't get married!\n");
		} else {
			printf("%d %d %d:%d\n", best[0], best[1], best[2], bestCost);
		}
	}
}
