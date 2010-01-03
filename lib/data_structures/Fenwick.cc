// Fenwick's Binary Indexed Tree.
// Ref. http://citeseer.ist.psu.edu/fenwick94new.html
#include <cstdio>
#include <cassert>
#include <vector>
using namespace std;

/*
 *  In this implementation, the tree is stored in a standard vector<int>.
 *  Elements are numbered by 0, 1, ..., n-1.
 *  tree[i] is sum of elements with indexes between i&(i+1) and i, inclusive.
 *  (this way, the trailing 1's of i act as a sort of a mask)
 *  Note: this is a bit different from what is proposed in Fenwick's article.
 */

class Fenwick {
	vector<int> tree;
public:
	// Creates a zero-initialized Fenwick tree for n elements.
	Fenwick(int n) { tree.assign(n, 0); }

	// Returns sum of elements a, a+1, ..., b.
	int sum(int a, int b) const {
		if (a == 0) {
			int s = 0;
			for (; b >= 0; b = (b & (b + 1)) - 1)
				s += tree[b];
			return s;
		} else {
			return sum(0, b) - sum(0, a-1);
		}
	}

	// Increases value of k-th element by x (can be negative)
	void inc(int k, int x) {
		for (; k < (int)tree.size(); k |= k + 1)
			tree[k] += x;
	}
};

int main()
{
	int n = 10;
	Fenwick tree(n);
	vector<int> value(n, 0);

	for (int cs = 0; cs < 1000000; cs++) {
		if (rand() % 100 < 20) {
			int k = rand() % n, inc = rand() % 2000 - 1000;
			tree.inc(k, inc);
			value[k] += inc;
			assert(tree.sum(k, k) == value[k]);
		} else {
			int a = rand() % n, b = rand() % n;
			if (a > b) swap(a, b);

			int sum = 0;
			for (int k = a; k <= b; k++) sum += value[k];

			assert(sum == tree.sum(a, b));
		}
	}
	printf("ok\n");
}


/*
#define MAXN 1000

int cum[MAXN+1];    // cum[n] = val[n] + val[n-1] + ... + val[n&(n-1) + 1]

// Returns sum of elements 1, 2, ..., n.
int sum(int n) {
	int s = 0;
	for (; n > 0; n &= n-1)
		s += cum[n];
	return s;
}

// Adds x to element n.  (1<=n<=MAXN)
void add(int n, int x) {
	for (; n <= MAXN; n += n & ~(n-1))
		cum[n] += x;
}
*/

