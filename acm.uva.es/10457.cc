#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct UnionFind {
	int p[210], r[210];

	void init(int N) {
		for (int i = 0; i <= N; i++) p[i] = i;
		for (int i = 0; i <= N; i++) r[i] = 0;
	}

	int f(int x) {
		int y = p[x], z;
		while (p[y] != y) y = p[y];
		while (p[x] != y) { z = p[x]; p[x] = y; x = z; }
		return y;
	}

	void u(int x, int y) {
		if (r[x] > r[y]) swap(x, y);
		p[x] = y;
		if (r[x] == r[y]) ++r[y];
	}
} uf;

struct Edge {
	int x, y, c;
	bool operator <(const Edge &other) const {
		return c < other.c;
	}
};

Edge E[1010];
int N, M, S, T;

int solve()
{
	if (S == T) return 0;

	sort(E, E+M);

	int best = E[M-1].c - E[0].c;
	for (int i = 0; i < M; i++) {
		uf.init(N);
		for (int j = i; j < M; j++) {
			int x = uf.f(E[j].x);
			int y = uf.f(E[j].y);
			if (x == y) continue;
			uf.u(x, y);
			if (uf.f(S) == uf.f(T)) {
				best = min(best, E[j].c - E[i].c);
				break;
			}
		}
	}

	return best;
}

int main()
{
	while (scanf("%d %d", &N, &M) == 2 && N > 0) {
		if (N == 0) break;
		assert(2 <= N && N <= 200);

		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &E[i].x, &E[i].y, &E[i].c);
		}

		int e1, e2, K;
		scanf("%d %d %d", &e1, &e2, &K);

		for (int i = 0; i < K; i++) {
			scanf("%d %d", &S, &T);
			printf("%d\n", e1 + e2 + solve());
		}
	}
}
