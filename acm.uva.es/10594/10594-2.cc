#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int N;
long long cost[102][128], cap[102][128], flow[102][128], INF=1LL<<61;
long long phi[102];

long long mcmf(int s, int t) {
	memset(flow, 0, sizeof(flow));
	memset(phi, 0, sizeof(phi));

	long long res = 0;

	while (true) {
		int prev[128], prev_rev[128];
		long long dist[128], pathcap[128];
		bool seen[128];

		for (int i = 0; i < N; i++) dist[i] = INF;
		dist[s] = 0;
		pathcap[s] = INF;
		memset(seen, 0, sizeof(seen));

		while (true) {
			int u = -1;
			for (int i = 0; i < N; i++)
				if (!seen[i] && (u < 0 || dist[i] < dist[u])) u = i;
			if (u < 0 || dist[u] >= INF) break;

			seen[u] = true;

			for (int v = 0; v < N; v++) {
				long long d = dist[u] + phi[u] + cost[u][v] - phi[v];
				if (flow[u][v] < cap[u][v] && dist[v] > d) {
					dist[v] = d;
					prev[v] = u;
					prev_rev[v] = 0;
					pathcap[v] = min(pathcap[u], cap[u][v] - flow[u][v]);
				}

				d = dist[u] + phi[u] - cost[v][u] - phi[v];
				if (flow[v][u] > 0 && dist[v] > d) {
					dist[v] = d;
					prev[v] = u;
					prev_rev[v] = 1;
					pathcap[v] = min(pathcap[u], flow[v][u]);
				}
			}
		}
		if (!seen[t]) break;

		res += pathcap[t] * (dist[t] - phi[s] + phi[t]);
		for (int v = t; v != s; v = prev[v]) {
			if (prev_rev[v] == 0)
				flow[prev[v]][v] += pathcap[t];
			else
				flow[v][prev[v]] -= pathcap[t];
		}

		for (int i = 0; i < N; i++)
			if (dist[i] < INF) phi[i] += dist[i];
	}

	return res;
}

int main() {
	int M;
	while (scanf("%d %d", &N, &M) == 2) {
		memset(cap, 0, sizeof(cap));
		memset(cost, 0, sizeof(cost));

		for (int i = 0; i < M; i++) {
			int x, y; long long c;
			scanf("%d %d %lld", &x, &y, &c);
			if (x == y) continue;
			cap[x][y] = cap[y][x] = 1;
			cost[x][y] = cost[y][x] = c;
		}

		long long K;
		scanf("%lld %lld", &cap[0][1], &K);

		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				cap[i][j] *= K;

		N++;
		long long res = mcmf(0, N-1);
		if (flow[0][1] != cap[0][1])
			printf("Impossible.\n");
		else
			printf("%lld\n", res);
	}
}
