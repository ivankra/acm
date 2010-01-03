// second best MST
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
using namespace std;

enum { MAXN = 200 };

struct UnionFind {
	int p[MAXN], rank[MAXN];

	void init(int N) {
		for (int i = 0; i < N; i++) {
			p[i] = i;
			rank[i] = 0;
		}
	}

	int f(int x) {
		int y = p[x], z;
		while (p[y] != y) y = p[y];
		while (p[x] != y) { z = p[x]; p[x] = y; x = z; }
		return y;
	}

	void u(int x, int y) {
		x = f(x);
		y = f(y);
		if (x != y) {
			if (rank[x] < rank[y]) {
				p[x] = y;
			} else if (rank[y] < rank[x]) {
				p[y] = x;
			} else {
				p[x] = y;
				++rank[y];
			}
		}
	}
};

struct Edge {
	int x, y, c;
	bool mst;

	bool operator <(const Edge &other) const {
		return c < other.c;
	}
};

int N, M;
Edge *E;
UnionFind uf;

void solve()
{
	sort(E, E+M);

	int mstCost = 0, mstSize = 0;
	uf.init(N);
	for (int i = 0; i < M; i++) {
		if (uf.f(E[i].x) != uf.f(E[i].y)) {
			uf.u(E[i].x, E[i].y);
			E[i].mst = true;
			mstSize++;
			mstCost += E[i].c;
		} else {
			E[i].mst = false;
		}
	}

	if (mstSize != N-1) {
		// graph is disconnected
		printf("No way\n");
		return;
	}

	if (M == N-1) {
		// no second MST
		printf("No second way\n");
		return;
	}

	int secondMstCost = 0x7fffffff;
	for (int ex = 0; ex < M; ex++) {
		if (!E[ex].mst) continue;

		int cost = 0, size = 0;
		uf.init(N);
		for (int i = 0; i < M; i++) {
			if (i == ex) continue;
			if (uf.f(E[i].x) != uf.f(E[i].y)) {
				uf.u(E[i].x, E[i].y);
				cost += E[i].c;
				size++;
			}
		}

		if (size == N-1) {
			secondMstCost = min(secondMstCost, cost);
		}
	}

	printf("%d\n", secondMstCost);
}

void readGraph() {
	scanf("%d %d", &N, &M);
	E = new Edge[M];
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &E[i].x, &E[i].y, &E[i].c);
		if (E[i].x == E[i].y) { M--; i--; continue; }
		E[i].x--;
		E[i].y--;
		E[i].mst = false;
	}
}

void cleanup() {
	delete[] E;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		readGraph();
		printf("Case #%d : ", cs);
		solve();
		cleanup();
	}
}
