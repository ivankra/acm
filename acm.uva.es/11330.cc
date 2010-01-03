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

int adj[10010][2], deg[10010], N;

void dfs(int x) {
	if (deg[x] == 0) return;
	assert(deg[x] == 2);
	deg[x] = 0;
	dfs(adj[x][0]);
	dfs(adj[x][1]);
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);

		memset(deg, 0, sizeof(deg));

		for (int i = 0; i < N; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			adj[x][deg[x]++] = y;
			adj[y][deg[y]++] = x;
		}

		int res = N;
		for (int i = 1; i <= 10000; i++) {
			if (deg[i] != 0) {
				dfs(i);
				res--;
			}
		}
		printf("%d\n", res);
	}
}
