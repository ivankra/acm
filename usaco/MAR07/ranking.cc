/*
ID: infnty1
LANG: C++
TASK: ranking
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

char a[1024][1024], seen[1024];
int M, N;
vector<int> adj[1024];

void dfs(int s, int x) {
	seen[x] = 1;
	a[s][x] = 1;
	for (int i = 0; i < (int)adj[x].size(); i++) {
		int y = adj[x][i];
		if (!seen[y]) dfs(s, y);
	}
}

int main() {
	freopen("ranking.in", "r", stdin);
	freopen("ranking.out", "w", stdout);

	scanf("%d %d", &N, &M);

	memset(a, 0, sizeof(a));
	for (int i = 0; i < M; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		a[x][y] = 1;
		adj[x].push_back(y);
	}

	for (int x = 1; x <= N; x++) {
		memset(seen, 0, sizeof(seen));
		dfs(x, x);
	}

	int res = 0;
	for (int x = 1; x <= N; x++)
		for (int y = x+1; y <= N; y++)
			if (a[x][y] == 0 && a[y][x] == 0) res++;
	printf("%d\n", res);
}
