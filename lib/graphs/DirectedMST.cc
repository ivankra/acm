// Reference:
// http://www.ce.rit.edu/~sjyeec/dmst.html

// Finds only the cost of directed MST.
// UVA 11183
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
using namespace std;

int INF = 0x3fffffff;

struct UnionFind {
	int head[1024], next[1024], size[1024], cc;

	void clear(int n) {
		for (int i = 0; i < n; i++) {
			head[i] = i;
			next[i] = -1;
			size[i] = 1;
		}
		cc = n;
	}

	inline int operator()(int x) const { return head[x]; }

	void merge(int x, int y) {
		x = head[x];
		y = head[y];
		if (x == y) return;
		if (size[x] < size[y]) swap(x, y);

		size[x] += size[y];
		cc--;
		while (y >= 0) {
			int yy = next[y];
			next[y] = next[x];
			next[x] = y;
			head[y] = x;
			y = yy;
		}
	}
} uf;

struct Edge { int x, y, c; };
vector<Edge> in[1024];
int N, parent[1024], parentCost[1024], answer;

// Chooses least cost incoming edge to component s
void choose(int s) {
	s = uf(s);
	parent[s] = -1;
	parentCost[s] = INF;
	if (uf(s) == uf(0)) return;
	for (int x = s; x >= 0; x = uf.next[x]) {
		for (int j = 0; j < (int)in[x].size(); j++) {
			if (uf(in[x][j].x) != uf(s) && in[x][j].c < parentCost[s]) {
				parent[s] = in[x][j].x;
				parentCost[s] = in[x][j].c;
			}
		}
	}
}

// Contracts a cycle into a single component
void contract(int s) {
	// add costs of edges in the cycle to the answer,
	// reduce costs of incoming edges
	for (int x = uf(s);;) {
		answer += parentCost[x];

		for (int a = x; a >= 0; a = uf.next[a]) {
			for (int i = 0; i < (int)in[a].size(); i++)
				in[a][i].c -= parentCost[x];
		}

		x = uf(parent[x]);
		if (x == uf(s)) break;
	}

	// merge cycle into a single component
	for (int x = uf(s);;) {
		int y = uf(parent[x]);
		if (uf(x) == uf(y)) break;
		uf.merge(x, y);
		x = y;
	}

	s = uf(s);
	choose(s);
}

int solve() {
	uf.clear(N);
	for (int i = 0; i < N; i++) choose(i);

	int seen[1024], tick = 1;
	memset(seen, 0, sizeof(seen));

	answer = 0;
	for (int s = 0; s < N; s++) {
		if (uf(s) != s || uf(s) == uf(0))
			continue;

		tick++;
		for (int y = uf(s); uf(y) != uf(0);) {
			if (seen[y] == tick) {
				contract(y);
				y = uf(y);
			}

			seen[y] = tick;
			if (parent[y] < 0)
				return INF;
			y = uf(parent[y]);
		}

		for (int y = uf(s); uf(y) != uf(0);) {
			answer += parentCost[y];
			uf.merge(y, 0);
			y = uf(parent[y]);
		}
	}

	return answer;
}

int main() {
	int T, M;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d %d", &N, &M) == 2; cs++) {
		for (int i = 0; i < N; i++) in[i].clear();
		for (int i = 0; i < M; i++) {
			Edge e;
			scanf("%d %d %d", &e.x, &e.y, &e.c);
			in[e.y].push_back(e);
		}

		int res = solve();
		printf("Case #%d: ", cs);
		if (res >= INF)
			printf("Possums!\n");
		else
			printf("%d\n", res);
	}
}
