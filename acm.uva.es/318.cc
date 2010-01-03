#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

#define INF (1LL << 62)

long long dist[512], adj[512][512];
int seen[512], N;

int main() {
	int m, x, y;

	for (int cs = 1; scanf("%d %d", &N, &m) == 2 && N > 0; cs++) {
		assert(1 <= N && N <= 510);

		printf("System #%d\n", cs);

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) adj[i][j] = INF;
			adj[i][i] = 0;
		}

		while (m-- > 0 && scanf("%d %d", &x, &y) == 2) {
			assert(x != y && adj[x][y] == INF);
			scanf("%lld", &adj[x][y]);
			assert(adj[x][y] >= 0);
			adj[y][x] = adj[x][y];
		}

		memset(seen, 0, sizeof(seen));
		for (int i = 1; i <= N; i++) dist[i] = INF;
		dist[1] = 0;

		for (;;) {
			int u = -1;
			for (int i = 1; i <= N; i++)
				if (!seen[i] && (u<0 || dist[i]<dist[u])) u=i;
			if (u < 0) break;

			assert(dist[u] < INF);

			seen[u] = 1;
			for (int v = 1; v <= N; v++)
				if (adj[u][v] != INF)
					dist[v] <?= dist[u] + adj[u][v];
		}

		long long res = 0;
		int resx=1, resy=1;

		for (int x = 1; x <= N; x++)
			if (2*dist[x] > res) { res = 2*dist[x]; resx = resy = x; }

		for (int x = 1; x <= N; x++)
		for (int y = x+1; y <= N; y++) {
			if (adj[x][y] == INF) continue;

			long long l = adj[x][y];
			if (dist[x] + l > dist[y] && dist[y] + l > dist[x]) {
				long long t = dist[x] + dist[y] + l;
				if (t > res) {
					res = t;
					resx = x;
					resy = y;
				}
			}
		}

		printf("The last domino falls after %lld.%d seconds, ",
				res/2, (int)((res%2)*5));

		if (resx == resy)
			printf("at key domino %d.\n\n", resx);
		else
			printf("between key dominoes %d and %d.\n\n", resx, resy);
	}
}
