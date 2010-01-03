// MST
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

struct Edge {
	int x, y, c;
	bool operator <(const Edge &other) const {
		return c < other.c;
	}
};

struct UnionFind {
	int p[1000100];
	char rank[1000100];

	void init(int N) {
		for (int i = 0; i < N; i++) p[i] = i;
		memset(rank, 0, N);
	}

	int f(int x) {
		int y = p[x], z;
		while (p[y] != y) y = p[y];
		while (p[x] != y) { z = p[x]; p[x] = y; x = z; }
		return y;
	}

	void u(int x, int y) {
		if (rank[x] < rank[y]) {
			p[x] = y;
		} else if (rank[y] < rank[x]) {
			p[y] = x;
		} else {
			p[x] = y;
			++rank[y];
		}
	}
};

int N, M;
Edge E[1000100];
UnionFind uf;

int findMst()
{
	int res = 0;
	sort(E, E+M);
	uf.init(N);
	for (int i = 0; i < M; i++) {
		int x = uf.f(E[i].x);
		int y = uf.f(E[i].y);
		if (x != y) {
			uf.u(x, y);
			res += E[i].c;
		}
	}
	return res;
}

int main()
{
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		if (cs != 1) printf("\n");

		int sum = 0;
		for (int i = 0; i < N-1; i++) {
			scanf("%d %d %d", &E[i].x, &E[i].y, &E[i].c);
			E[i].x--; E[i].y--;
			sum += E[i].c;
		}
		printf("%d\n", sum);

		scanf("%d", &M);
		M += N-1;
		for (int i = N-1; i < M; i++) {
			scanf("%d %d %d", &E[i].x, &E[i].y, &E[i].c);
			E[i].x--; E[i].y--;
		}
		printf("%d\n", findMst());

		int K;
		scanf("%d", &K);
		for (int i = 0; i < K; i++) scanf("%*d %*d %*d");
	}
}
