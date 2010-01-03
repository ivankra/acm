/*
ID: infnty1
PROB: schlnet
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int adj[128][128], N;

int main() {
	freopen("schlnet.in", "r", stdin);
	freopen("schlnet.out", "w", stdout);

	scanf("%d", &N);
	memset(adj, 0, sizeof(adj));
	for (int x = 1; x <= N; x++) {
		int y;
		while (scanf("%d", &y) == 1 && y > 0)
			adj[x][y] = 1;
		adj[x][x] = 1;
	}

	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			if (adj[i][k])
				for (int j = 1; j <= N; j++)
					adj[i][j] |= adj[k][j];

	int scc[128], rep[128], nscc = 0;
	for (int x = 1; x <= N; x++) scc[x] = -1;

	for (int x = 1; x <= N; x++) {
		if (scc[x] != -1) continue;
		rep[++nscc] = x;
		for (int y = 1; y <= N; y++)
			if (adj[x][y] && adj[y][x]) scc[y] = nscc;
	}

	int A = nscc, B = nscc;
	for (int x = 1; x <= nscc; x++) {
		for (int y = 1; y <= nscc; y++)
			if (x != y && adj[rep[y]][rep[x]]) { A--; break; }
		for (int y = 1; y <= nscc; y++)
			if (x != y && adj[rep[x]][rep[y]]) { B--; break; }
	}

	printf("%d\n", A);
	printf("%d\n", nscc<=1 ? 0 : max(A, B));
}
