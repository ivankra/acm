// Implementation of Kruskal's minimum spanning tree algorithm.
// Time complexity: O(E log E)
// Input format: integers separated by whitespaces in order: N, M, then
// M triples of integers u, v, c specifying the edges. Vertices are labelled
// by integers 1..N.
// Output: description of MST in the same format as the input.
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

// Implementation of union-find data structure with path compression and
// union by rank heuristics.
struct UnionFind {
	int *p;
	char *rank;

	UnionFind(int N) : p(new int[N]), rank(new char[N]) {
		for (int i = 0; i < N; i++) p[i] = i;
		memset(rank, 0, sizeof(rank));
	}

	~UnionFind() {
		delete[] rank;
		delete[] p;
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
			if (rank[x] < rank[y]) p[x] = y;
			else if (rank[y] < rank[x]) p[y] = x;
			else { p[x] = y; ++rank[y]; }
		}
	}

private:
	UnionFind(const UnionFind &) {}
	void operator =(const UnionFind &){}
};

struct Edge {
	int u, v, cost;

	bool operator <(const Edge &other) const {
		return cost < other.cost;
	}
};

vector<Edge> kruskal(int N, vector<Edge> E)
{
	sort(E.begin(), E.end());

	UnionFind uf(N+1);

	vector<Edge> mst;
	mst.reserve(N-1);

	for (vector<Edge>::const_iterator e = E.begin(); e != E.end(); ++e) {
		if (uf.f(e->u) != uf.f(e->v)) {
			uf.u(e->u, e->v);
			mst.push_back(*e);
		}
	}

	return mst;
}

int main()
{
	int N, M;
	assert(scanf("%d %d", &N, &M) == 2);
	assert(N >= 1 && M >= 0);

	vector<Edge> E(M);
	for (int i = 0; i < M; i++) {
		Edge &e = E[i];
		assert(scanf("%d %d %d", &e.u, &e.v, &e.cost) == 3);
		assert(1 <= e.u && e.u <= N);
		assert(1 <= e.v && e.v <= N);
	}

	E = kruskal(N, E);
	M = E.size();

	printf("%d %d\n", N, M);
	for (int i = 0; i < M; i++) {
		printf("%d %d %d\n", E[i].u, E[i].v, E[i].cost);
	}

	return 0;
}
