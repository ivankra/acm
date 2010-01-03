#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int N, G[256][256], H[256][256];
int next[256];

void doit()
{
	// start with arbitrary cycle
	for (int i = 0; i < N; i++)
		next[i] = (i + 1) % N;

	for (;;) {
		// Find edge u->v in the cycle, which isn't in the graph
		int u, v;
		for (u = 0; u < N; u++) {
			v = next[u];
			if (!G[u][v]) break;
		}
		if (u >= N) break;  // we're done

		// find edge x->y in the cycle, such that (u,x) and (v,y) are in the graph
		// (it must exist for deg(u)+deg(v)>=n property:
		// consider set S of vertices adjacent to v, and T of vertices, which follow
		// vertices adjacent to u in cycle. |S|+|T| = deg(u)+deg(v) >= n, ==>
		// they must have a common vertex y, and x is its predecessor in current cycle.)
		int x, y;
		for (x = 0; x < N; x++) {
			y = next[x];
			if (G[u][x] && G[v][y]) break;
		}

		if (x >= N) {
			// violation of deg(u)+deg(v) >= n property
			printf("N\n");
			return;
		}

		// reverse subpath v->...->x
		for (int a = v; a != x;) {
			int b = next[a];
			next[b] = a;
			a = b;
		}

		next[u] = x;
		next[v] = y;
	}

	printf("1");
	for (int x = 0;;) {
		x = next[x];
		printf(" %d", x+1);
		if (x == 0) break;
	}
	printf("\n");
}

int main()
{
	int x, y;
	while (scanf("%d", &N) == 1 && N > 0) {
		memset(G, 0, sizeof(G));
		while (scanf(" %d %d", &x, &y) == 2) {
			x--; y--;
			if (x == y) continue;
			G[x][y] = G[y][x] = 1;
		}
		scanf(" %%");
		doit();
	}
}
