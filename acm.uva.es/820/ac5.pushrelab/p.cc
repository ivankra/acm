#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

#define MAXN 128

int adj[MAXN][MAXN], deg[MAXN];   // adjacency lists
int res[MAXN][MAXN], n, s, t;     // res[x][y] = residual capacity of edge (x,y)
int height[MAXN], excess[MAXN];

void global_relab() {
	int qu[MAXN];

	fill(height, height+n, 2*n);

	for (int pass = 0; pass < 1 /*FIXME*/; pass++) {
		if (pass == 0)
			height[qu[0] = t] = 0;
		else
			height[qu[0] = s] = n;

		for (int head = 0, tail = 1; head < tail; head++) {
			int y = qu[head];
			for (int x = 0; x < n; x++) {
				if (res[x][y] > 0 && height[x] > height[y]+1) {
					height[x] = height[y] + 1;
					qu[tail++] = x;
				}
			}
		}
	}
	height[s] = n;
}

int push_relabel() {
	fill(excess, excess+n, 0);
	fill(height, height+n, 0);
	height[s] = n;

	queue<int> q;	// queue of overflowing vertices.

	for (int i = 0; i < deg[s]; i++) {
		int x = adj[s][i], c = res[s][x];
		res[s][x] -= c;
		res[x][s] += c;
		excess[x] += c;
		excess[s] -= c;
		if (x != s && x != t) q.push(x);
	}

	int g = 0;

	while (!q.empty()) {
		int x = q.front(), newh = 2*n;

		// with this 'if', the function will find value of max flow
		// faster, but when it terminates, the flow will not be
		// a valid flow, just a preflow (there will be overflowing
		// vertices)
		if (height[x] >= n) { q.pop(); continue; }    // FIXME

		for (int i = 0; excess[x] > 0 && i < deg[x]; i++) {
			int y = adj[x][i];
			if (res[x][y] == 0) continue;

			if (height[x] != height[y] + 1) {
				newh <?= height[y] + 1;
				continue;
			}

			int d = (res[x][y] <? excess[x]);
			res[x][y] -= d;
			res[y][x] += d;
			excess[x] -= d;
			excess[y] += d;

			if (excess[y] == d && (y != s && y != t)) q.push(y);
		}

		if (excess[x] == 0) {
			q.pop();
			continue;
		}

		height[x] = newh;
		if (++g == n) { g = 0; global_relab(); }
	}

	return excess[t];
}

int main()
{
	int m, x, y, z;
	for (int cs = 1; scanf("%d %d %d %d", &n, &s, &t, &m) == 4 && n > 0; cs++) {
		memset(res, 0, sizeof(res));
		memset(deg, 0, sizeof(deg));
		s--; t--;
		while (m-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3) {
			if (z <= 0 || x == y) continue;
			x--; y--;
			if (res[x][y] == 0) {
				adj[x][deg[x]++] = y;
				adj[y][deg[y]++] = x;
			}
			res[y][x] = (res[x][y] += z);
		}
		printf("Network %d\nThe bandwidth is %d.\n\n", cs, push_relabel());
	}
}
