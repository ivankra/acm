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

int N;
unsigned cost[1024][1024];

unsigned solve()
{
	unsigned dist[1024], seen[1024], res = 0;
	for (int i = 0; i <= N; i++) {
		dist[i] = 0xFFFFFFFF;
		seen[i] = 0;
	}

	dist[1] = 0;
	for (;;) {
		int u = -1;
		for (int i = 1; i <= N; i++)
			if (!seen[i] && (u < 0 || dist[i] < dist[u])) u = i;
		if (u < 0) break;

		seen[u] = 1;
		res += dist[u];

		for (int v = 1; v <= N; v++) {
			dist[v] <?= cost[u][v];
		}
	}

	return res;
}

int main()
{
	int T, M, x, y;
	unsigned price, c;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%u %d %d", &price, &N, &M);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++)
				cost[i][j] = 0xFFFFFFFF;
			cost[i][i] = 0;
		}

		for (int i = 0; i < M; i++) {
			scanf("%d %d %u", &x, &y, &c);
			if (c < cost[x][y])
				cost[x][y] = cost[y][x] = c;
		}

		printf("%u\n", price * solve());
	}
}
