/*
 *  Segment tree.
 *
 *  Supports:
 *    adding a fixed value X to all elements in a given range in O(log n)
 *    finding sum of all elements in a given range in O(log n)
 */

#include <cassert>
#include <vector>
using namespace std;

struct SegTree {
        /*
         *  Tree is stored like a binary heap.  The root (tree[0]) represents
         *  all elements.  Left/right child of a node represents first/second
         *  half of its range.
         */
	struct Node { int sum, added; };
        vector<Node> tree;
        int n;

        int left(int x) { return 2*x+1; }
        int right(int x) { return 2*x+2; }

        /* Allocates at least 'need' elements, all initialized to 0. */
	SegTree(int need) {
		for (n = 4; n < need; n <<= 1);
		tree = vector<Node>(2*n-1);
		for (int i = 0; i < (int)tree.size(); i++)
			tree[i].sum = tree[i].added = 0;
	}

	void update(int x, int range) {
		int a = tree[x].added;
		tree[x].sum += range * a;
		tree[x].added = 0;
		if (x < n-1) {
			tree[left(x)].added += a;
			tree[right(x)].added += a;
		}
	}

	/* Adds s to all elements in range [0, m-1]. */
	void add(int m, int s) {
		if (m == 0) return;
		for (int x = 0, r = n;;) {
			assert(1 <= m && m <= r);
			if (m == r) { tree[x].added += s; return; }

			update(x, r);
			tree[x].sum += m * s;

			r /= 2;
			if (m > r) {
				tree[left(x)].added += s;
				x = right(x);
				m -= r;
			} else {
				x = left(x);
			}
		}
	}

        /* Returns sum of all elements in range [0, m-1]. */
	int sum(int m) {
		if (m == 0) return 0;
		for (int s = 0, x = 0, r = n;;) {
			/* we're at node x, which represents a range with
			   r elements, and we want s+(the sum of first m of them). */

			assert(1 <= m && m <= r);

			update(x, r);
			if (m == r) return s + tree[x].sum;

			r /= 2;
			if (m > r) {
				update(left(x), r);
				s += tree[left(x)].sum;
				m -= r;
				x = right(x);
			} else {
				x = left(x);
			}
		}
	}

	/* ADD and SUM operations on ranges [a, b] */
	void add(int a, int b, int s) { add(b+1, s); add(a, -s); }
	int sum(int a, int b) { return sum(b+1) - sum(a); }
};
