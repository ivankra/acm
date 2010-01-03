#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Graph {
	int N;
	int all, deg[32], adj[32], label[32];

	Graph(int n) {
		N = n;
		for (int i = 0; i < N; i++) {
			adj[i] = 1 << i;
			deg[i] = 0;
			label[i] = i;
		}
		all = (1 << N) - 1;
	}

	void add(int u, int v) {
		if (u != v && !adjacent(u, v)) {
			adj[u] |= 1 << v;
			adj[v] |= 1 << u;
			deg[u]++;
			deg[v]++;
		}
	}

	bool adjacent(int x, int y) const {
		return (adj[x] & (1 << y)) != 0;
	}

	void dfs(int seen[], int x, int id) const {
		if (seen[x] == 0) {
			seen[x] = id;
			for (int y = 0; y < N; y++)
				if (adjacent(x, y)) dfs(seen, y, id);
		}
	}

	vector<Graph> components() const {
		vector<Graph> out;
		int seen[32];
		for (int i = 0; i < N; i++) seen[i] = 0;

		int id = 0;
		for (int x = 0; x < N; x++) {
			if (seen[x] != 0) continue;
			dfs(seen, x, ++id);

			int v[32], m = 0;
			for (int y = 0; y < N; y++)
				if (seen[y] == id) v[m++] = y;

			for (int i = 0; i < m; i++)
				for (int j = i; j >= 1 && deg[v[j-1]] < deg[v[j]]; j--)
					swap(v[j-1], v[j]);

			Graph G(m);
			for (int i = 0; i < m; i++) {
				G.label[i] = label[v[i]];
				for (int j = 0; j < m; j++)
					if (i != j && adjacent(v[i], v[j]))
						G.add(i, j);
			}
			out.push_back(G);
		}

		return out;
	}
};

struct VertexCover {
	const Graph &G;
	vector<int> &out;
	int covAfter[32], best, bestSize;

	VertexCover(const Graph &G, vector<int> &out) : G(G), out(out) {}

	void go(int i, int cur, int cov) {
		int curSize = 0;
		for (int t = cur; t > 0; t &= t - 1) curSize++;
		if (curSize >= bestSize) return;

		if (i == G.N) {
			if (cov == G.all) {
				best = cur;
				bestSize = curSize;
			}
			return;
		}

		if ((cov | covAfter[i]) != G.all) return;

		go(i+1, cur|(1<<i), cov|G.adj[i]);

		if ((cur & (1 << i)) != 0) return;
		if ((G.adj[i] & (~cur) & ((1<<i)-1)) != 0) return;
		go(i+1, (cur|G.adj[i]) & ~(1<<i), cov);
	}

	void solve() {
		if (G.N <= 1) return;

		if (G.N == 2) {
			out.push_back(G.label[0]);
			return;
		}

		covAfter[G.N] = 0;
		for (int i = G.N-1; i >= 0; i--)
			covAfter[i] = covAfter[i+1] | G.adj[i];

		best = (1 << G.N) - 1;
		bestSize = G.N;
		go(0, 0, 0);

		for (int i = 0; i < G.N; i++)
			if (best & (1 << i)) out.push_back(G.label[i]);
	}
};

int main() {
	int T, N, M;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d %d", &N, &M) == 2; cs++) {
		Graph G(N);
		for (int i = 0; i < M; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			G.add(u, v);
		}

		vector<Graph> cc = G.components();

		vector<int> res;
		for (int i = 0; i < (int)cc.size(); i++) {
			VertexCover c(cc[i], res);
			c.solve();
		}
		sort(res.begin(), res.end());

		printf("Case #%d: %d\n", cs, (int)res.size());
		for (int i = 0; i < (int)res.size(); i++)
			printf(i==0 ? "%d" : " %d", res[i]);
		printf("\n");
	}
}
