#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
using namespace std;

int sh[128][128], N, INF=999999;
int D[128][128];

vector<int> Q[128];

void check(int u, int v, int d) {
	if (d <= N && d < D[u][v]) {
		D[u][v] = d;
		Q[d].push_back(u*256+v);
	}
}

int main() {
	int M;
	for (int cs = 1; scanf("%d %d", &N, &M) == 2 && N > 0; cs++) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				sh[i][j] = (i == j ? 0 : INF);

		for (int i = 0; i < M; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			x--; y--;
			assert(0 <= x && x < N && 0 <= y && y < N);
			if (x != y)
				sh[x][y] = 1;
		}

		for (int k = 0; k < N; k++)
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					sh[i][j] = min(sh[i][j], sh[i][k] + sh[k][j]);

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				D[i][j] = INF;
		D[0][0] = 1;

		for (int i = 0; i <= N; i++)
			Q[i].clear();
		Q[1].push_back(0);

		int res = 1;
		while (res <= N) {
			if (Q[res].empty()) { res++; continue; }

			int u = Q[res].back() >> 8;
			int v = Q[res].back() & 255;
			Q[res].pop_back();

			if (u == 1 && v == 1) break;
			if (D[u][v] != res) continue;

			if (u != v && sh[u][v] < INF)
				check(v, u, res + sh[u][v] - 1);

			for (int w = 0; w < N; w++) {
				if (sh[u][w] < INF) check(w, v, res + sh[u][w]);
				if (sh[w][v] < INF) check(u, w, res + sh[w][v]);
				if (w != u && w != v && sh[u][w] < INF && sh[w][v] < INF)
					check(w, w, res + sh[u][w] + sh[w][v] - 1);
			}
		}

		printf("Network %d\n", cs);
		if (res > N)
			printf("Impossible\n\n");
		else
			printf("Minimum number of nodes = %d\n\n", res);
	}
}
