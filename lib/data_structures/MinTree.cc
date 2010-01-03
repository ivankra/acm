// MinTree.  A modification of segments tree which allows to find
// a minimum element in a range, as well as its position in O(log n) time.
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

struct MinTree {
	int *tree, *index, N;
	
	MinTree(int sz) {
		for (N = 1; N < sz+5; N *= 2);
		tree = new int[2*N];
		index = new int[2*N];
		for (int i = 0; i < N; i++) index[N+i] = i;
	}

	void update(int k, int x) {
		for (tree[k += N] = x; k != 1;) {
			k >>= 1;
			if (tree[2*k] <= tree[2*k+1]) {
				tree[k] = tree[2*k];
				index[k] = index[2*k];
			} else {
				tree[k] = tree[2*k+1];
				index[k] = index[2*k+1];
			}
		}
	}

	int minIndex(int a, int b) {
		if (a == b) return a;
		int res = tree[a+N] <= tree[b+N] ? a : b;
		for (a += N, b += N;; a >>= 1, b >>= 1) {
			if ((a >> 1) == (b >> 1)) return res;
			if ((a & 1) == 0 && tree[a+1] < tree[N+res]) res = index[a+1];
			if ((b & 1) == 1 && tree[b-1] < tree[N+res]) res = index[b-1];
		}
	}
};

int main() {
	int N = 1000;
	MinTree S(N);
	vector<int> V(N);

	for (int i = 0; i < N; i++) {
		V[i] = rand();
		S.update(i, V[i]);
	}

	for (int t = 0; t < 1000; t++) {
		for (int a = 0; a < N; a++) {
			int mi = V[a];
			for (int b = a; b < N; b++) {
				mi <?= V[b];
				int i = S.minIndex(a, b);
				assert(a <= i && i <= b && V[i] == mi);
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
