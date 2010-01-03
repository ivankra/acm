#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

struct Edge {
	int x, y;
	Edge(int X, int Y) {
		x = X;
		y = Y;
		if (x > y) swap(x, y);
	}
	bool operator <(const Edge &e) const {
		return x < e.x || (x == e.x && y < e.y);
	}
};

char themap[512][512];
int boss[512][512], cnt[512*512], N, K;
vector< vector<int> > adj;

char dfs1_ch;
int dfs1(int r, int c) {
	if (themap[r][c] != dfs1_ch || boss[r][c] >= 0) return 0;
	boss[r][c] = N;
	return 1 + dfs1(r-1, c) + dfs1(r+1, c) + dfs1(r, c-1) + dfs1(r, c+1);
}

int tick, st[512*512], low[512*512], cut[512*512];
void dfs2(int x, int p) {
	st[x] = low[x] = tick;
	tick++;

	for (int i = 0; i < (int)adj[x].size(); i++) {
		int y = adj[x][i];
		if (y == p) continue;

		if (st[y] == 0) {
			dfs2(y, x);
			if (low[y] == st[y]) {
				if (cnt[x] >= K) cut[y] = 1;
			}
			low[x] = min(low[x], low[y]);
		} else {
			low[x] = min(low[x], st[y]);
		}
	}
}

void dfs3(int x) {
	if (st[x] || cut[x]) return;
	st[x] = 1;

	for (int i = 0; i < (int)adj[x].size(); i++)
		dfs3(adj[x][i]);
}

int main()
{
	int width, height;
	scanf("%d %d %d", &height, &width, &K);

	memset(themap, 0, sizeof(themap));
	memset(boss, 0, sizeof(boss));
	for (int r = 1; r <= height; r++) {
		for (int c = 1; c <= width; c++) {
			scanf(" %c", &themap[r][c]);
			boss[r][c] = -1;
		}
	}

	N = 1;
	memset(cnt, 0, sizeof(cnt));
	for (int r = 1; r <= height; r++) {
		for (int c = 1; c <= width; c++) {
			if (boss[r][c] < 0) {
				dfs1_ch = themap[r][c];
				cnt[N] = dfs1(r, c);
				N++;
			}
		}
	}

#ifdef DEBUG
	for (int r = 1; r <= height; r++) {
		for (int c = 1; c <= width; c++) {
			printf("%3d", boss[r][c]);
		}
		printf("\n");
	}
	printf("N=%d\n", N);
#endif

	vector<Edge> E;
	for (int r = 1; r <= height; r++) {
		for (int c = 1; c <= width; c++) {
			for (int d = 0; d < 4; d++) {
				int r1 = r + "0211"[d] - '1';
				int c1 = c + "1102"[d] - '1';
				if (boss[r][c] != boss[r1][c1]) {
					E.push_back(Edge(boss[r][c], boss[r1][c1]));
				}
			}
		}
	}
	sort(E.begin(), E.end());

	adj.assign(N, vector<int>());
	for (int i = 0; i < (int)E.size(); i++) {
		if (i > 0 && E[i-1].x == E[i].x && E[i-1].y == E[i].y) continue;

		adj[E[i].x].push_back(E[i].y);
		adj[E[i].y].push_back(E[i].x);
	}

	tick = 1;
	memset(st, 0, sizeof(st));
	memset(low, 0, sizeof(low));
	memset(cut, 0, sizeof(cut));
	dfs2(0, -1);

	memset(st, 0, sizeof(st));
	dfs3(0);

	int res = 0;
	for (int x = 1; x < N; x++) {
		if (st[x] == 0 || cnt[x] >= K)
			res += cnt[x];
	}
	printf("%d\n", res);

	return 0;
}
