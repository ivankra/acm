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

int N, N1, N2;
int color[2010], size1, size2;
vector<int> adj[2010];

bool dfs(int x)
{
	if (color[x] == 1) size1++; else size2++;

	for (int i = 0; i < (int)adj[x].size(); i++) {
		int y = adj[x][i];
		if (color[y] == 0) {
			color[y] = color[x] == 1 ? 2 : 1;
			if (!dfs(y)) return false;
		} else if (color[y] != (color[x] == 1 ? 2 : 1)) {
			return false;
		}
	}

	return true;
}

bool solve()
{
	vector<pair<int, int> > V;
	memset(color, 0, sizeof(color));
	for (int i = 1; i <= N; i++) {
		if (color[i] == 0) {
			size1 = size2 = 0;
			color[i] = 1;
			if (!dfs(i)) return false;
			V.push_back(make_pair(size1, size2));
		}
	}

	static bool dp[2010], next[2010];
	for (int i = 0; i <= N; i++) dp[i] = false;
	dp[0] = true;

	for (int i = 0; i < (int)V.size(); i++) {
		for (int j = 0; j <= N; j++)
			next[j] = false;

		for (int j = 0; j <= N; j++) {
			if (dp[j]) {
				next[j + V[i].first] = true;
				next[j + V[i].second] = true;
			}
		}

		for (int j = 0; j <= N; j++)
			dp[j] = next[j];
	}

	return dp[N1];
}

int main()
{
	int T, M, x, y;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d", &N1, &N2, &M);
		N = N1 + N2;
		for (int i = 0; i <= N; i++) adj[i].clear();
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &x, &y);
			if (x == y) continue;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}

		if (solve())
			printf("yes\n");
		else
			printf("no\n");
	}
}
