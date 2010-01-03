#include <cstdio>
#include <cstring>

#define INF 0x1fffffff

int G[1024][1024], dist[1024], N;

int dijkstra(int s, int t) {
	int seen[1024];
	for (int i = 0; i < N; i++) dist[i] = INF, seen[i] = 0;

	dist[s] = 0;

	for (;;) {
		int u = -1;
		for (int i = 0; i < N; i++)
			if (!seen[i] && (u < 0 || dist[i] < dist[u])) u = i;
		if (u < 0) break;

		seen[u] = 1;
		for (int v = 0; v < N; v++)
			dist[v] <?= dist[u] + G[u][v];
	}

	return dist[t];
}

int main() {
	int n, m, x, y, z;
	for (int cs = 1; scanf("%d %d", &n, &m) == 2; cs++) {
		N = n*2;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) G[i][j] = INF;
			G[i][i] = 0;
		}

		while (m-- > 0 && scanf("%d %d %d", &x, &y, &z)) {
			G[x][n+y] <?= z; G[y][n+x] <?= z;
			G[n+x][y] <?= z; G[n+y][x] <?= z;
		}


		int res = dijkstra(0, n-1);

		printf("Set #%d\n", cs);
		if (res < INF) printf("%d\n", res); else printf("?\n");
	}
}
