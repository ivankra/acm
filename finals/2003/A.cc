// ICPC Finals 2003 - Problem A - Building Bridges
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

struct UnionFind {
	int p[65536];

	void clear(int n) {
		for (int i = 0; i < n; i++)
			p[i] = i;
	}

	int f(int n) {
		if (p[p[n]] != p[n])
			p[n] = f(p[n]);
		return p[n];
	}

	void u(int x, int y) {
		x = f(x);
		y = f(y);
		if (x != y) {
			if (rand() & 1) {
				swap(x, y);
			}
			p[x] = y;
		}
	}
};

char grid[128][128];
int R, C;
set<int> B;
UnionFind uf;

int V(int y, int x) {
	return y * (C + 1) + x;
}

struct Edge {
	int u, v, cost;
	Edge(int u_, int v_, int c_) : u(u_), v(v_), cost(c_) {}
	bool operator <(const Edge &e) const {
		return cost < e.cost;
	}
};

int main()
{
	for (int cs = 1; scanf("%d %d", &R, &C) == 2; cs++) {
		if (R == 0 || C == 0) break;

		if (cs > 1) printf("\n");
		printf("City %d\n", cs);

		memset(grid, '.', sizeof(grid));
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				scanf(" %c", &grid[i][j]);
			}
		}

		uf.clear((R+5)*(C+5));
		B.clear();

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (grid[i][j] == '#') {
					uf.u(V(i, j), V(i+1, j));
					uf.u(V(i, j), V(i+1, j+1));
					uf.u(V(i, j), V(i, j+1));
					B.insert(V(i, j));
					B.insert(V(i+1, j));
					B.insert(V(i, j+1));
					B.insert(V(i+1, j+1));
				}
			}
		}

		vector<Edge> E;

		static int dx[] = { 1, -1, 0, 0 };
		static int dy[] = { 0, 0, 1, -1 };

		for (set<int>::const_iterator it = B.begin(); it != B.end(); ++it) {
			int u = *it;
			int y0 = u / (C + 1);
			int x0 = u % (C + 1);
			for (int dir = 0; dir < 4; dir++) {
				int y = y0 + dy[dir], x = x0 + dx[dir], len = 1;
				while (0 <= y && y <= R && 0 <= x && x <= C) {
					int v = V(y, x);
					if (B.count(v) != 0) {
						if (uf.f(u) != uf.f(v)) {
							E.push_back(Edge(u, v, 1000000 + len));
						}
						break;
					}
					y += dy[dir];
					x += dx[dir];
					len++;
				}
			}
		}

		sort(E.begin(), E.end());

		long long cost = 0;

		for (int i = 0; i < (int)E.size(); i++) {
			int u = uf.f(E[i].u);
			int v = uf.f(E[i].v);
			if (u != v) {
				cost += E[i].cost;
				uf.u(u, v);
			}
		}

		set<int> zzz;
		for (set<int>::const_iterator it = B.begin(); it != B.end(); ++it) {
			zzz.insert(uf.f(*it));
		}

		int groups = zzz.size();

//printf("cost=%lld g=%d\n", cost, groups);

		if (groups <= 1 && cost == 0) {
			printf("No bridges are needed.\n");
		} else if (cost == 0) {
			printf("No bridges are possible.\n");
		} else {
			printf("%lld bridge%s of total length %lld\n",
				cost/1000000, cost/1000000 == 1 ? "" : "s",
				cost%1000000);
		}

		if (groups >= 2) {
			printf("%d disconnected groups\n", groups);
		}
	}
}
