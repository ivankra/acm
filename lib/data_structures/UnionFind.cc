#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

struct UnionFind {
	int n, m, *p, *r;
	
	UnionFind(int N) : n(N), m(N), p(new int[N]), r(new int[N]) {
		for (int i = 0; i < n; i++) { p[i] = i; r[i] = 0; }
	}

	~UnionFind() { delete[] p; delete[] r; }

	int f(int x) {
		int y, z;
		assert(0 <= x && x < n);
		for (z = p[x]; z != p[z]; z = p[z]);
		for (; x != z; x = y) { y = p[x]; p[x] = z; }
		return z;
	}

	void u(int x, int y) {
		assert(0 <= x && x < n && 0 <= y && y < n);
		if ((x=f(x)) != (y=f(y))) {
			if (r[x] > r[y]) swap(x, y);
			p[x] = y; r[y] += (r[x] == r[y]); m--;
		}
	}

private:
	UnionFind(const UnionFind &){}
	UnionFind &operator =(const UnionFind &){return *this;}
};


// Disjoint sets.
// Linked list representation, O(m + n log n) time for m calls to u().
struct UnionFind2 {
	vector<int> next, head, sz;

	UnionFind2(int N) {
		next = head = vector<int>(N, -1);
		for (int i = 0; i < N; i++) head[i] = i;
		sz = vector<int>(N, 1);
	}

	// Returns a representative of the set, containing x.
	int f(int x) const { return head[x]; }
	int operator()(int x) const { return head[x]; }

	// Merges sets, containing x and y.
	void u(int x, int y) {
		x = head[x]; y = head[y];
		if (x != y) {
			if (sz[x] < sz[y]) swap(x, y);
			while (y >= 0) {
				int z = next[y];
				head[y] = x;
				next[y] = next[x];
				next[x] = y;
				y = z;
			}
		}
	}

	// Enumerates all elements of the set, containing x.
	void foreach(int x, void (*fn)(int)) {
		for (x = head[x]; x >= 0; x = next[x]) fn(x);
	}

	// Returns size of the set, containing x.
	int size(int x) const { return sz[head[x]]; }

	// Returns total number of elements.
	int size() const { return head.size(); }


	void dump() {
		int m = 0;
		for (int x = 0; x < size(); x++) {
			if (x != head[x]) continue;
			if (m++) printf(", ");
			printf("{");
			for (int y = x; y >= 0; y = next[y])
				printf(x==y ? "%d" : ", %d", y);
			printf("}");
		}
		printf("\n");
	}
};
