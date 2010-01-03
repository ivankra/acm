#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

const int MaxN = 10010;

int N;
int adj[MaxN][16], deg[MaxN], pv[MaxN], low[MaxN], seen[MaxN], id;

void dfs(int x, int p = -1) {
	id++;
	seen[x] = low[x] = id;

	bool art = false;
	pv[x] = 0;

	for (int i = 0; i < deg[x]; i++) {
		int y = adj[x][i];
		if (y == p) continue;

		if (seen[y] == 0) {
			dfs(y, x);
			low[x] <?= low[y];

			if (low[y] >= seen[x]) {
				art = true;
				pv[x]++;
			}
		} else {
			low[x] <?= seen[y];
		}
	}

	if (p < 0 && pv[x] <= 1) art = false;

	if (art) {
		if (p >= 0) pv[x]++;
	} else {
		pv[x] = 1;
	}
}

int main()
{
	int K, x, y;
	while (scanf("%d %d", &N, &K) == 2 && N > 0) {
		for (int i = 0; i < N; i++) deg[i] = seen[i] = 0;

		while (scanf("%d %d", &x, &y) == 2 && x >= 0) {
			adj[x][deg[x]++] = y;
			adj[y][deg[y]++] = x;
		}

		id = 0;
		dfs(0);

		vector<int> v;
		for (int x = 0; x < N; x++)
			v.push_back((pv[x] << 16) + N-x);
		sort(v.begin(), v.end());
		reverse(v.begin(), v.end());

		for (int i = 0; i < K; i++)
			printf("%d %d\n", N-(v[i]&0xffff), v[i]>>16);
		printf("\n");
	}
}
