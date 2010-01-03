// Segments tree.  Maintains an array, and allows to change an element and
// compute an associative operation over a consecutive range of elements in
// O(log n) time.
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

struct SegTree {
	int *tree, N;   // N is a power of 2, size of tree is 2*N.  o(x,y) is associative.
	inline int o(int x, int y) { return min(x, y); }
	SegTree(int sz) { for (N = 1; N < sz+5; N *= 2); tree = new int[2*N]; }
	void update(int k, int x) {
		for (tree[k += N] = x; k != 1;) { k >>= 1; tree[k] = o(tree[2*k], tree[2*k+1]); }
	}
	int range(int a, int b) {
		if (a == b) return tree[a+N];
		for (int L = tree[a += N], R = tree[b += N];; a >>= 1, b >>= 1) {
			if ((a >> 1) == (b >> 1)) return o(L, R);
			if ((a & 1) == 0) L = o(L, tree[a+1]);
			if ((b & 1) == 1) R = o(tree[b-1], R);
		}
	}
};


int main() {
	int N = 1000;
	SegTree S(N);
	vector<int> V(N);

	for (int i = 0; i < N; i++) {
		V[i] = rand();
		S.update(i, V[i]);
	}

	for (int t = 0; t < 1000; t++) {
		for (int a = 0; a < N; a++) {
			int mi = V[a];
			for (int b = a; b < N; b++) {
				if (b > a) mi <?= V[b];
				assert(mi == S.range(a, b));
			}
		}

		for (int k = 0; k < 100; k++) {
			int pos = rand() % N;
			int val = rand();
			V[pos] = val;
			S.update(pos, val);
		}

		printf("%d\n", t);
	}

	printf("ok\n");
}
