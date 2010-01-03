#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
typedef long long LL;

int seen[1024], N;
vector<int> seq;
char adj[1024][1024];

int scc[1024], dp[1024];
vector<int> sccV[1024];

int f(int x) {
	if (dp[x] != -1) return dp[x];
	assert(scc[x] == x);
	dp[x] = sccV[x].size();

	for (int i = 0; i < (int)sccV[x].size(); i++) {
		int y = sccV[x][i];
		for (int z = 0; z < N; z++) {
			if (adj[y][z] && scc[z] != x) {
				dp[x] >?= (int)sccV[x].size() + f(scc[z]);
			}
		}
	}

	return dp[x];
}

void dfs1(int x) {
	if (seen[x]) return;
	seen[x] = 1;
	for (int y = 0; y < N; y++)
		if (adj[x][y]) dfs1(y);
	seq.push_back(x);
}

void dfs2(int x, int id) {
	if (scc[x] != -1) return;
	scc[x] = id;
	sccV[id].push_back(x);
	for (int y = 0; y < N; y++) {
		if (adj[y][x]) dfs2(y, id);
	}
}

int main()
{
	int T, M, x, y;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++)
			memset(adj[i], 0, N);

		for (int i = 0; i < M; i++) {
			scanf("%d %d", &x, &y);
			if (x == y) continue;
			adj[x-1][y-1] = 1;
		}

		memset(seen, 0, sizeof(seen));
		seq.clear();
		for (int i = 0; i < N; i++) {
			if (!seen[i]) dfs1(i);
		}

		for (int i = 0; i < 1024; i++) sccV[i].clear();
		memset(scc, 0xff, sizeof(scc));
		assert((int)seq.size() == N);
		for (int i = N-1; i >= 0; i--) {
			x = seq[i];
			if (scc[x] == -1) {
				dfs2(x, x);
			}
		}

		memset(dp, 0xff, sizeof(dp));
		int best = 0;
		for (int i = 0; i < N; i++) {
			if (scc[i] == i) {
				best >?= f(i);
			}
		}
		printf("%d\n", best);
	}
}
