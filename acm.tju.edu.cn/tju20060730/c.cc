#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> VI;  typedef vector<VI> VVI;

int N, cost[20000], scc[20000], cheap[20000], nscc;
VI ord;
VVI adj, adjrev;

void dfs(int x) {
	scc[x] = 1;
	for (int i = 0; i < (int)adj[x].size(); i++) {
		int y = adj[x][i];
		if (scc[y] < 0) dfs(y);
	}
	ord.push_back(x);
}

void dfs2(int x, int id) {
	scc[x] = id;
	cheap[id] <?= cost[x];
	for (int i = 0; i < (int)adjrev[x].size(); i++) {
		int y = adjrev[x][i];
		if (scc[y] < 0) dfs2(y, id);
	}
}

int main() {
	int M, x, y;
	while (scanf("%d %d", &N, &M) == 2) {
		if (N==0 && M==0) break;
		for (int i = 0; i < N; i++) scanf("%d", &cost[i]);

		adj.assign(N, VI());
		adjrev.assign(N, VI());
		while (M-- > 0 && scanf("%d %d", &x, &y) == 2) {
			x--; y--;
			if (x != y) {
				adj[x].push_back(y);
				adjrev[y].push_back(x);
			}
		}

		ord.clear();

		memset(scc, 0xff, sizeof(scc));
		for (int i = 0; i < N; i++)
			if (scc[i] < 0) dfs(i);

		memset(scc, 0xff, sizeof(scc));
		memset(cheap, 0x3f, sizeof(cheap));
		nscc = 0;
		for (int i = N-1; i >= 0; i--) {
			int x = ord[i];
			if (scc[x] < 0) {
				cheap[nscc] = cost[x];
				dfs2(x, nscc);
				nscc++;
			}
		}

		for (int x = 0; x < N; x++) {
			for (int i = 0; i < (int)adj[x].size(); i++) {
				int y = adj[x][i];
				if (scc[x] != scc[y])
					cheap[scc[y]] = 0;
			}
		}

		int res = 0;
		for (int i = 0; i < nscc; i++)
			res += cheap[i];
		printf("%d\n", res);
	}
}
