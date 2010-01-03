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

long long mcmf(int s, int t) {
	memset(flow, 0, sizeof(flow));

	long long res = 0;

	while (true) {
		int prev[128], prev_rev[128];
		long long dist[128], pathcap[128];

		for (int i = 0; i <= N; i++) dist[i] = INF;
		dist[s] = 0;
		pathcap[s] = INF;

		while (true) {
			bool flag = false;
			for (int i = 0; i <= N; i++) {
				for (int j = 0; j <= N; j++) {
					if (flow[i][j] < cap[i][j] && dist[j] > dist[i] + cost[i][j]) {
						dist[j] = dist[i] + cost[i][j];
						prev[j] = i;
						prev_rev[j] = 0;
						pathcap[j] = min(pathcap[i], cap[i][j] - flow[i][j]);
						flag = true;
					}
					if (flow[j][i] > 0 && dist[j] > dist[i] - cost[j][i]) {
						dist[j] = dist[i] - cost[j][i];
						prev[j] = i;
						prev_rev[j] = 1;
						pathcap[j] = min(pathcap[i], flow[j][i]);
						flag = true;
					}
				}
			}
			if (!flag) break;
		}

		if (dist[t] >= INF) break;

		res += pathcap[t] * dist[t];
		for (int v = t; v != s; v = prev[v]) {
			if (prev_rev[v] == 0)
				flow[prev[v]][v] += pathcap[t];
			else
				flow[v][prev[v]] -= pathcap[t];
		}
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

		long long res = mcmf(0, N);
		if (flow[0][1] != cap[0][1])
			printf("Impossible.\n");
		else
			printf("%lld\n", res);
	}
}
