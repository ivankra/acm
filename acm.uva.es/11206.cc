// backtracking
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

int N, adj[32], color[32], colored[4], value[4], best;

void rec(int used, int sum) {
	if (used == (1 << N) - 1) {
		best >?= sum;
		return;
	}

	int x = -1, xv = -1;
	for (int i = 0; i < N; i++) {
		if (used & (1 << i)) continue;

		int v = 0;
		for (int j = 0; j < 4; j++)
			v += (colored[j] & adj[i]) != 0;

		if (v > xv) { x = i; xv = v; }
	}

	for (int c = 0; c < 4; c++) {
		if ((adj[x] & colored[c]) != 0) continue;

		color[x] = c;
		colored[c] |= 1 << x;

		int newsum = sum;
		for (int y = 0; y < N; y++) {
			if (adj[x] & used & (1 << y)) {
				int t = value[c] - value[color[y]];
				newsum += t * t;
			}
		}

		rec(used | (1 << x), newsum);

		colored[c] ^= 1 << x;
	}
}

int main() {
	int M, x, y;

	while (scanf("%d %d %d %d %d %d", &N, &M, &value[0], &value[1], &value[2], &value[3]) == 6 && N > 0) {
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &x, &y);
			x--; y--;
			if (x != y) {
				adj[x] |= 1 << y;
				adj[y] |= 1 << x;
			}
		}

		memset(colored, 0, sizeof(colored));
		best = 0;
		rec(0, 0);
		printf("%d\n", best);
	}
}
