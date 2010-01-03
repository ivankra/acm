#include <stdio.h>

/* Implements height-balanced AVL tree */

#define max(a,b) (((a) > (b)) ? (a) : (b))

#define MAXN 32768

static int left[MAXN], right[MAXN], key[MAXN], count[MAXN], parent[MAXN];
static int height[MAXN], root, nr_nodes;

/* Left rotation. Returns previous value of right[x] */
static int rotl(int x)
{
	int y;

	if ((y = right[x]) == 0)
		return x;

	right[x] = left[y];
	parent[right[x]] = x;

	parent[y] = parent[x];

	if (parent[y] == 0)
		root = y;
	else if (left[parent[y]] == x)
		left[parent[y]] = y;
	else
		right[parent[y]] = y;

	left[y] = x;
	parent[x] = y;

	count[x] = count[left[x]] + 1 + count[right[x]];
	count[y] = count[x] + 1 + count[right[y]];

	height[x] = 1 + max(height[left[x]], height[right[x]]);
	height[y] = 1 + max(height[left[y]], height[right[y]]);

	return y;
}

/* Right rotation. Returns previous value of left[x] */
static int rotr(int x)
{
	int y;

	if ((y = left[x]) == 0)
		return x;

	left[x] = right[y];
	parent[left[x]] = x;

	parent[y] = parent[x];

	if (parent[y] == 0)
		root = y;
	else if (left[parent[y]] == x)
		left[parent[y]] = y;
	else
		right[parent[y]] = y;

	right[y] = x;
	parent[x] = y;

	count[x] = count[left[x]] + 1 + count[right[x]];
	count[y] = count[x] + 1 + count[left[y]];

	height[x] = 1 + max(height[left[x]], height[right[x]]);
	height[y] = 1 + max(height[left[y]], height[right[y]]);

	return y;
}

/* Inserts specified leaf node into height-balanced AVL tree */
static void insert(int leaf)
{
	int x, t;

	if (root == 0) {
		root = leaf;
		return;
	}

	/* Insert leaf into binary tree, increment count fields along the path */
	for (x = root;;) {
		count[x]++;

		if (key[leaf] < key[x]) {
			if (left[x] == 0) {
				left[x] = leaf;
				break;
			}
			x = left[x];
		} else {
			if (right[x] == 0) {
				right[x] = leaf;
				break;
			}
			x = right[x];
		}
	}
	parent[leaf] = x;

	/* Rebalance tree by rotations and update height fields. */
	while (x != 0) {
		height[x] = 1 + max(height[left[x]], height[right[x]]);

		if ((height[left[x]] - height[right[x]]) > 1) {
			t = left[x];
			if (height[right[t]] > height[left[t]])
				rotl(t);

			x = rotr(x);
		} else if ((height[right[x]] - height[left[x]]) > 1) {
			t = right[x];
			if (height[left[t]] > height[right[t]])
				rotr(t);

			x = rotl(x);
		}

		x = parent[x];
	}
}

/* Returns (n+1)-th smallest element (n = 0, 1, 2...) */
static int order(int n)
{
	int r, c;

	for (r = root; r != 0;) {
		c = count[left[r]];

		if (n > c) {
			n = n - c - 1;
			r = right[r];
		} else if (n < c) {
			r = left[r];
		} else {
			return r;
		}
	}

	return 0;
}

int main()
{
	static int a[32768], u[32768], t, n, m;
	int i, c, r;

	for (scanf("%d", &t); t-- > 0 && scanf("%d%d", &m, &n) == 2;) {
		for (i = 0; i < m; i++)
			scanf("%d", &a[i]);

		for (i = 0; i < n; i++)
			scanf("%d", &u[i]);

		count[0] = height[0] = 0;
		nr_nodes = 1;
		root = 0;

		for (i = 0, c = 0; i < n; i++) {
			while (c < u[i]) {
				/* Create and initialize leaf node */
				r = nr_nodes++;
				left[r] = right[r] = parent[r] = 0;
				height[r] = count[r] = 1;
				key[r] = a[c++];

				insert(r);
			}

			r = order(i);
			if (r == 0) { char *p; for (p=NULL;;)*p++=42; }

			printf("%d\n", key[r]);
		}

		if (t > 0)
			printf("\n");
	}

	return 0;
}
