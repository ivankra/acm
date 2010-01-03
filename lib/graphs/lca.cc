// O(n log n) preprocessing, O(log n) query LCA and level ancestors algorithms
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

#define MAXN     1000
#define LOG_MAXN 10              // should be around log_2(MAXN)

int parent[MAXN], depth[MAXN], N;
int kparent[LOG_MAXN+1][MAXN];   // parent[k][x] = 2^k-th ancestor of x, or root if none

int lca(int x, int y) {
	if (depth[y] > depth[x])
		swap(x, y);

	// climb x to the same level as y
	for (int k = LOG_MAXN; k >= 0; k--)
		while ((1 << k) <= depth[x] - depth[y])
			x = kparent[k][x];
	if (x == y) return x;

	for (int k = LOG_MAXN; k >= 0; k--) {
		while (kparent[k][x] != kparent[k][y]) {
			x = kparent[k][x];
			y = kparent[k][y];
		}
	}
	assert(x != y && parent[x] == parent[y]);
	return parent[x];
}

int kthParent(int x, int k)
{
	for (int i = LOG_MAXN; i >= 0; i--) {
		while ((1 << i) <= k) {
			x = kparent[i][x];
			k -= (1 << i);
		}
	}
	return x;
}

int levelAncestor(int x, int k) { return kthParent(x, depth[x] - k); }

int lca_slow(int x, int y) {
	while (x != y) {
		if (depth[y] > depth[x]) swap(x, y);
		x = parent[x];
	}
	return x;
}

void fillDepth(int x) {
	if (depth[x] == -1) {
		fillDepth(parent[x]);
		depth[x] = 1 + depth[parent[x]];
	}
}

int main()
{
	srand(921657361);

	for (int cs = 1; cs <= 10; cs++) {
		N = max(10, rand() % (MAXN - 10));
	
		// generate a random tree
		parent[0] = 0;
		for (int x = 1; x < N; x++)
			parent[x] = rand() % x;

		// fill 2^k-th parents table
		for (int x = 0; x < N; x++)
			kparent[0][x] = parent[x];
		for (int k = 1; k <= LOG_MAXN; k++)
			for (int x = 0; x < N; x++)
				kparent[k][x] = kparent[k-1][ kparent[k-1][x] ];

		// fill node depths table
		for (int x = 0; x < N; x++) depth[x] = -1;
		depth[0] = 0;
		for (int x = 1; x < N; x++) fillDepth(x);

		for (int x = 0; x < N; x++)
			for (int y = 0; y < N; y++)
				assert(lca(x, y) == lca_slow(x, y));

		printf("Test %d (N=%d) OK\n", cs, N);
	}
}
