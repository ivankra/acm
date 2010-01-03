#include <cstdio>
#include <cassert>
#include <cstring>
typedef long long int64;

#define INF (1LL<<50)
#define MAXN 610

int N, src;
int deg[MAXN], adj[MAXN][MAXN], cost[MAXN][MAXN], got[MAXN][MAXN];
int64 ansNum[MAXN], ansDen[MAXN], dist[MAXN], distNew[MAXN];

int main()
{
	int m;
	for (int cs = 1; scanf("%d %d %d", &N, &m, &src) == 3; cs++) {
		assert(1 <= N && N <= 600);
		assert(0 <= m && m <= 5000);
		assert(0 <= src && src < N);

		memset(deg, 0, sizeof(deg));

		for (int i = 0; i < m; i++) {
			int x, y, c;
			scanf("%d %d %d", &x, &y, &c);

			assert(0 <= x && x < N);
			assert(0 <= y && y < N);
			assert(0 <= c && c <= 100000);

			if (got[x][y] != cs) {
				got[x][y] = cs;
				cost[x][y] = c;
				adj[x][deg[x]++] = y;
			}

			if (c < cost[x][y])
				cost[x][y] = c;
		}

		for (int i = 0; i < N; i++)
			ansNum[i] = ansDen[i] = dist[i] = INF;

		dist[src] = 0;
		for (int k = 1; k <= 1000; k++) {
			for (int x = 0; x < N; x++)
				distNew[x] = INF;

			for (int x = 0; x < N; x++) {
				if (dist[x] == INF) continue;
				for (int i = 0; i < deg[x]; i++) {
					int y = adj[x][i];
					distNew[y] <?= dist[x] + cost[x][y];
				}
			}

			for (int x = 0; x < N; x++) {
				dist[x] = distNew[x];

				if (dist[x] == INF) continue;
				if (ansNum[x] == INF ||
				    dist[x]*ansDen[x] < ansNum[x]*k) {
					ansNum[x] = dist[x];
					ansDen[x] = k;
				}
			}
		}

		int q;
		scanf("%d", &q);

		for (int i = 0; i < q; i++) {
			int x;
			scanf("%d", &x);
			assert(0 <= x && x < N);

			if (x == src)
				printf("0.0000 0\n");
			else if (ansNum[x] == INF)
				printf("No Path\n");
			else
				printf("%.4f %d\n",
					(ansNum[x]+0.0)/ansDen[x],
					(int)ansDen[x]);
		}
		printf("\n");
	}
}
