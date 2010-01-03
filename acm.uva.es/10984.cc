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

int N, color[1024], match[1024], seen[1024];
vector<int> adj[1024];

bool dfs(int x, int col) {
	if (color[x] != -1)
		return color[x] == col;

	color[x] = col;
	for (int i = 0; i < (int)adj[x].size(); i++)
		if (!dfs(adj[x][i], 1-col)) return false;
	return true;
}

bool aug(int x) {
	if (seen[x]) return false;
	seen[x] = 1;

	for (int i = 0; i < (int)adj[x].size(); i++) {
		int y = adj[x][i];
		if (match[y] < 0 || aug(match[y])) {
			match[y] = x;
			match[x] = y;
			return true;
		}
	}

	return false;
}

bool solve() {
	if (N % 2 != 0) return false;

	memset(color, 0xff, sizeof(color));
	for (int i = 1; i <= N; i++)
		if (color[i] < 0 && !dfs(i, 0)) return false;

	for (int i = 1; i <= N; i++)
		sort(adj[i].begin(), adj[i].end());

	vector<int> v;
	memset(match, 0xff, sizeof(match));
	for (int i = 1; i <= N; i++) {
		memset(seen, 0, sizeof(seen));
		if (match[i] < 0 && color[i] == 0) {
			if (!aug(i)) return false;
			v.push_back(i);
		}
	}

	printf("%d\n", N/2);
	for (int i = 0; i < (int)v.size(); i++)
		printf(i == 0 ? "%d" : " %d", v[i]);
	printf("\n");

	return true;
}

int main() {
	int T, M;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d %d", &N, &M) == 2; cs++) {
		for (int i = 0; i <= N; i++) adj[i].clear();

		for (int i = 0; i < M; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			adj[x].push_back(y);
			adj[y].push_back(x);
		}

		printf("Case #%d: ", cs);
		if (!solve())
			printf("Impossible\n");
	}
}
