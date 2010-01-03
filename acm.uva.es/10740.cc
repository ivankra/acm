#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define INF 0x3fffffff

struct Edge {
	int u, v, cost;
	int num;
};

int N, M, K, source, sink, dist[20][200], seen[200];
Edge E[2000], *prev[20][200];
vector<Edge *> adj[200];

int solve()
{
	for (int k = 0; k <= K; k++) {
		for (int x = 1; x <= N; x++) {
			dist[k][x] = INF;
			prev[k][x] = NULL;
		}
	}

	memset(seen, 0, sizeof(seen));

	for (int k = 1; k <= K; k++) {
		if (k == 1) {
			dist[k][source] = 0;
		} else {
			for (int i = 0; i < M; i++) {
				Edge *e = &E[i];
				if (e->num+1 < k && dist[e->num+1][e->u] + e->cost < dist[k][e->v]) {
					dist[k][e->v] = dist[e->num+1][e->u] + e->cost;
					prev[k][e->v] = e;
				}
			}
		}

		// Dijkstra
		while (true) {
			int u = -1;
			for (int x = 1; x <= N; x++) {
				if (seen[x] < k && (u < 0 || dist[k][x] < dist[k][u])) u = x;
			}
			if (u < 0 || dist[k][u] >= INF) break;

			Edge *e = prev[k][u];
			if (e != NULL) {
//				printf("  u=%d k=%d: predecessor is u=%d k=%d cost=%d\n",
//					u, k, e->u, e->num, e->cost);
				assert(e->v == u);
				e->num++;
			}

			seen[u] = k;

			for (vector<Edge *>::iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
				e = *it;
				if (dist[k][u] + e->cost < dist[k][e->v]) {
					assert(seen[e->v] < k);
					dist[k][e->v] = dist[k][u] + e->cost;
					prev[k][e->v] = e;
				}
			}
		}

//		printf("%dth path from %d to %d: %d\n", k, source, sink, dist[k][sink]);
	}

	return dist[K][sink];
}

bool in(int x, int a, int b) { return a <= x && x <= b; }

int main()
{
	while (scanf("%d %d %d %d %d", &N, &M, &source, &sink, &K) == 5) {
		if (N == 0 && M == 0) break;
		assert(in(N,2,100) && in(M,1,1000) && in(K,1,10) && in(source,1,N) && in(sink,1,N));

		for (int i = 1; i <= N; i++)
			adj[i].clear();

		for (int i = 0; i < M; i++) {
			Edge &e = E[i];
			assert(scanf("%d %d %d", &e.u, &e.v, &e.cost) == 3);
			assert(in(e.u, 1, N) && in(e.v, 1, N) && in(e.cost, 0, 10000));
			e.num = 0;
			adj[e.u].push_back(&E[i]);
		}

		int res = solve();
		printf("%d\n", res < INF ? res : -1);
	}
}
