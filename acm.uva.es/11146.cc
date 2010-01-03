#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

double INF = 1.0 / 0.0;

double cost[128][128], cap[128][128];
int adj[128][128], N;

double aug(int s, int t) {
	int seen[128], p[128], q[128]={s}, qh=0, qt=1;
	memset(seen, 0, sizeof(seen));

	while (qh < qt && !seen[t]) {
		int x = q[qh++];
		seen[x] = 1;
		for (int y = 0; y < N; y++) {
			if (adj[x][y] && cap[x][y] > 1e-6 && !seen[y]) {
				seen[q[qt++] = y] = 1;
				p[y] = x;
			}
		}
	}
	if (!seen[t]) return -1;

	double c = INF;
	for (int x = t; x != s; x = p[x]) {
		if (cap[p[x]][x] != INF)
			c = min(c, cap[p[x]][x]);
	}

	for (int x = t; x != s; x = p[x]) {
		if (cap[p[x]][x] != INF) {
			cap[p[x]][x] -= c;
			cap[x][p[x]] += c;
		}
	}

	return c;
}

bool compute(int s, int t, double dist[]) {
	int reach[128];
	memset(reach, 0, sizeof(reach));

	for (int i = 0; i < N; i++) dist[i] = INF;
	dist[s] = 0.0;
	reach[s] = 1;

	for (int k = 0; k <= N; k++) {
		for (int x = 0; x < N; x++) {
			for (int y = 0; y < N; y++) {
				if (adj[x][y] && reach[x] && (!reach[y] || dist[x] + cost[x][y] < dist[y])) {
					reach[y] = 1;
					dist[y] = dist[x] + cost[x][y];
				}
			}
		}
	}

	return reach[t] != 0;
}

int in(int x) { return 2*x; }
int out(int x) { return 2*x+1; }

int main()
{
	int T, M;
	for (scanf("%d", &T); T--;) {
		scanf("%d %d", &N, &M);
		N *= 2;

		memset(adj, 0, sizeof(adj));
		for (int x = 0; x < N/2; x++) {
			double c;
			if (x == 0 || x == N/2-1) c = 0; else scanf("%lf", &c);
			adj[in(x)][out(x)] = 1;
			cost[in(x)][out(x)] = c;
		}

		int orig_adj[64][64];
		memset(orig_adj, 0, sizeof(orig_adj));

		for (int i = 0; i < M; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			x--; y--;
			if (x < 0 || x >= N/2 || y < 0 || y >= N/2 || x == y || orig_adj[x][y]) continue;
			orig_adj[x][y] = orig_adj[y][x] = 1;

			adj[out(x)][in(y)] = 1;
			cost[out(x)][in(y)] = 0;

			adj[out(y)][in(x)] = 1;
			cost[out(y)][in(x)] = 0;
		}

		if (orig_adj[0][N/2-1]) {
			printf("No Solution!\n");
			continue;
		}

		double dist1[128], dist2[128];
		if (!compute(in(0), out(N/2-1), dist1) || !compute(in(N/2-1), out(0), dist2)) {
			printf("0.0000\n");
			continue;
		}

		for (int x = 0; x < N; x++)
			for (int y = 0; y < N; y++)
				cap[x][y] = INF;

		for (int x = 0; x < N/2; x++) {
			double c = (x == 0 || x == N/2-1) ? INF : (dist1[out(x)] + dist2[out(x)]);
			c = max(0.0, c);
			adj[in(x)][out(x)] = adj[out(x)][in(x)] = 1;
			cap[in(x)][out(x)] = cap[out(x)][in(x)] = c;
		}

		double a, flow = 0;
		while ((a = aug(in(0), out(N/2-1))) > 0.0)
			flow += a;
		printf("%.4f\n", flow);
	}
}
