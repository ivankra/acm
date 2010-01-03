#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <cmath>
#include <cassert>
#include <map>
using namespace std;

vector<int> adj[2000];
int bfsOrder[2000];

bool cmp(int x, int y) { return bfsOrder[x] < bfsOrder[y]; }

void reconstruct(vector<int> bfs, vector<int> dfs)
{
	int n = bfs.size();
	assert(bfs.size() == dfs.size() && dfs.size() > 0 && bfs[0] == dfs[0]);

	int root = bfs[0];
	if (n <= 1) return;

	assert(bfs[1] == dfs[1]);

	int k = 1, z = -1;
	while (k+1 < n && bfs[k+1] > bfs[k]) {
		if (bfsOrder[bfs[k+1]] != bfsOrder[bfs[k]] + 1) break;
		if (bfs[k+1] == z) break;
		if (z == -1 && dfs[k+1] != bfs[k+1]) z = dfs[k+1];
		k++;
	}

	for (int i = 1; i <= k; i++)
		adj[root].push_back(bfs[i]);

	vector<int> d, b;
	for (int i = 1, j = 0; ; i++) {
		if (i == n || (j < k && dfs[i] == adj[root][j])) {
			if (d.size() != 0) {
				b = d;
				sort(b.begin(), b.end(), cmp);
				reconstruct(b, d);
			}

			d.clear();
			j++;
		}
		if (i == n) break;
		d.push_back(dfs[i]);
	}
}

void do_dfs(int x, vector<int> &res) {
	res.push_back(x);
	for (int i = 0; i < adj[x].size(); i++)
		do_dfs(adj[x][i], res);
}

void do_bfs(int s, vector<int> &res) {
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		res.push_back(x);
		for (int i = 0; i < adj[x].size(); i++)
			q.push(adj[x][i]);
	}
}

int main()
{
	int N;
	while (scanf("%d", &N) == 1 && N > 0) {
		vector<int> dfs(N), bfs(N);
		for (int i = 0; i < N; i++) { scanf("%d", &bfs[i]); bfsOrder[bfs[i]] = i; }
		for (int i = 0; i < N; i++) scanf("%d", &dfs[i]);

		for (int i = 0; i <= N; i++) adj[i].clear();
		reconstruct(bfs, dfs);

		for (int i = 1; i <= N; i++) {
			printf("%d:", i);
			for (int j = 0; j < adj[i].size(); j++) printf(" %d", adj[i][j]);
			printf("\n");
		}

/*		int root = bfs[0];
		bfs.clear(); dfs.clear();
		do_bfs(root, bfs);
		do_dfs(root, dfs);
		printf("bfs':");
		for (int i = 0; i < bfs.size(); i++) printf(" %d", bfs[i]); printf("\n");
		printf("dfs':");
		for (int i = 0; i < dfs.size(); i++) printf(" %d", dfs[i]); printf("\n\n");*/
	}
}
