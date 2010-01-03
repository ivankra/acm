/* Splay tree */
/*
Analysis:

Define arbitary node weights w(x), e.g. w(x)=1.
Define s(x) = sum_{y in subtree of x} w(y)
Define node rank r(x) = log_2 s(x).
Potential of the tree phi(T) = sum_{x in T} r(x)

We shall find amortized cost of each splay step in terms of the number of
rotations.  (Only three of the six cases are shown; others are symmetric.)

1) Zig-zig step:
     r(z)  z                       x  r'(x) 
          / \                     / \
   r(y)  y   D                   A   y  r'(y)
        / \        -------->        / \
 r(x)  x   C      rotate z-y,      B   z  r'(z)
      / \         rotate y-x          / \
     A   B                           C   D

We need this inequality:
  [r(x) + r'(z)]/2 = [lg(s(x)) + lg(s'(z))] / 2   (by concavity of log)
  <= lg[(s(x) + s'(z)) / 2]                       (note: s'(x) >= s(x)+s'(z))
  <= lg(s'(x) / 2) = r'(x) - 1.
Hence: r'(z) <= 2 r'(x) - r(x) - 2.

amortized cost of zig-zag =
  = actual_cost + phi' - phi                      (actual cost = 2 rotations)
  = 2 + [r'(x) + r'(y) + r'(z)] - [r(x) + r(y) + r(z)]
  = 2 + (r'(x) - r(z)) + r'(y) + r'(z) - r(x) - r(y)
              =0        >=r'(x)                 <=r(x)
  <= 2 + r'(x) + r'(z) - 2 r(x)
  <= 2 + r'(x) + [2 r'(x) - r(x) - 2] - 2 r(x)
  = 3 (r'(x) - r(x)).
 
2) Zig-zag step:
       z
      / \                         x
     y   D                      /   \
    / \        -------->      y       z
   A   x      rotate x-y,    / \     / \
      / \     rotate x-z    A   B   C   D
     B   C
Analysis is almost identical to the zig-zig case.

3) Zig step
     y              x
    / \            / \
   x   C   --->   A   y
  / \                / \
 A   B              C   D
amortized cost = 1 + phi' - phi = 1 + r'(x) + r'(y) - r(x) - r(y)
  = 1 + r'(y) - r(x) <= 1 + r'(x) - r(x)
  <= 3(r'(x) - r(x)) + 1.

Ranks in amortized costs telescope, and thus any sequence of m splay steps
on node x with at most one zig step need amortized 3(r'(x) - r(x)) + 1 rotations,
where r'(x) and r(x) are ranks of x after/before the sequence of splay steps.

Choosing w(x)=1 yields r(x) <= lg(n=size of the tree),
thus splaying to root is amortized O(log n) time.

Insertion: first insert new node as a leaf (you can show that total increase
of potential is O(log n)), then then splay the new node to root.
*/
#include <cstdio>
#include <cassert>

struct SplayNode {
	SplayNode *left, *right, *parent;
	int size;
	int key;

	explicit SplayNode(int k) :
	left(0), right(0), parent(0), size(1), key(k) {}

	void updateSize() {
		size = 1 + (left == 0 ? 0 : left->size) + (right == 0 ? 0 : right->size);
	}
};

// Rotates edge x - x's parent.
void rotate(SplayNode *x)
{
	SplayNode *y = x->parent, *z = y->parent;
	if (x == y->left) {
		y->left = x->right;
		if (x->right != NULL) x->right->parent = y;
		x->right = y;
		y->parent = x;
	} else {
		y->right = x->left;
		if (x->left != NULL) x->left->parent = y;
		x->left = y;
		y->parent = x;
	}

	x->parent = z;
	if (z != NULL) {
		if (z->left == y) z->left = x;
		else z->right = x;
	}

	y->updateSize();
	x->updateSize();
}

// Splays node x to root, returns x (the new root)
SplayNode *splay(SplayNode *x)
{
	if (x == NULL) return NULL;
	while (x->parent != NULL) {
		SplayNode *y = x->parent, *z = y->parent;
		if (z == NULL) {
			// zig
			rotate(x);
			break;
		}
		if ((y->left == z) == (z->left == y)) {
			// zig-zig
			rotate(y);
			rotate(x);
		} else {
			// zig-zag
			rotate(x);
			rotate(x);
		}
	}
	return x;
}

SplayNode *splay(SplayNode *root, int key)
{
	SplayNode *x = root;
	while (x != NULL && x->key != key) {
		SplayNode *y = (key < x->key) ? x->left : x->right;
		if (y == NULL) break;
		x = y;
	}
	return splay(x);
}

SplayNode *insert(SplayNode *root, int key)
{
	SplayNode *x = root, *y = NULL, *z = new SplayNode(key);
	while (x != NULL) {
		y = x;
		x->size++;
		if (key < x->key) x = x->left; else x = x->right;
	}

	z->parent = y;
	if (y != NULL) {
		if (key < y->key) y->left = z; else y->right = z;
	}

	return splay(z);
}

SplayNode *join(SplayNode *a, SplayNode *b)
{
	if (a != NULL) a->parent = NULL;
	if (b != NULL) b->parent = NULL;
	if (a == NULL) return b;
	if (b == NULL) return a;
	while (a->right != NULL) a = a->right;
	splay(a);
	a->right = b;
	b->parent = a;
	a->updateSize();
	return a;
}

SplayNode *remove(SplayNode *x)
{
	splay(x);
	SplayNode *y = join(x->left, x->right);
	delete x;
	return y;
}




// Test code and comparison with treaps
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Treap {
	Treap *left, *right;
	int key, aux, size;

	explicit Treap(int x) :
	left(NULL), right(NULL), key(x), aux(rand()), size(1) {}

	void updateSize() {
		size = 1 + (left == 0 ? 0 : left->size) + (right == 0 ? 0 : right->size);
	}

	static Treap *rotLeft(Treap *x) {
		Treap *y = x->right;
		x->right = y->left;
		y->left = x;
		x->updateSize();
		y->updateSize();
		return y;
	}

	static Treap *rotRight(Treap *x) {
		Treap *y = x->left;
		x->left = y->right;
		y->right = x;
		x->updateSize();
		y->updateSize();
		return y;
	}

	static Treap *insert(Treap *root, int key) {
		if (root == NULL) return new Treap(key);
		if (key < root->key) {
			root->left = insert(root->left, key);
			root->updateSize();
			if (root->left->aux < root->aux)
				root = rotRight(root);
		} else {
			root->right = insert(root->right, key);
			root->updateSize();
			if (root->right->aux < root->aux)
				root = rotLeft(root);
		}
		return root;
	}

	static Treap *find(Treap *root, int key) {
		while (root != NULL) {
			if (key < root->key) root = root->left;
			else if (root->key < key) root = root->right;
			else break;
		}
		return root;
	}
};

void traverse(SplayNode *x, vector<int> &out) {
	if (x != NULL) {
		traverse(x->left, out);
		out.push_back(x->key);
		traverse(x->right, out);
	}
}

int main()
{
	SplayNode *s = NULL;
	Treap *treap = NULL;

	int	seed = 91750587,
		tests = 200000,
		prob_insert = 30,
		min_keys = 5000;

	vector<int> keys;
	keys.reserve(tests+10);

	srand(seed);
	keys.clear();
	int t1 = clock();
	for (int cs = 0; cs < tests; cs++) {
		if (keys.size() < min_keys || (rand() % 100) < prob_insert) {
			int key = rand();
			keys.push_back(key);

			s = insert(s, key);
		} else {
			int i = rand() % keys.size();
			int key = keys[i];
			keys[i] = keys.back();
			keys.pop_back();

			s = splay(s, key);
			assert(s != NULL && s->key == key);
		}
	}
	t1 = clock() - t1;
	printf("Splay: %d ms\n", t1);

	srand(seed);
	keys.clear();
	int t2 = clock();
	for (int cs = 0; cs < tests; cs++) {
		if (keys.size() < min_keys || (rand() % 100) < prob_insert) {
			int key = rand();
			keys.push_back(key);

			treap = Treap::insert(treap, key);
		} else {
			int i = rand() % keys.size();
			int key = keys[i];
			keys[i] = keys.back();
			keys.pop_back();

			Treap *x = Treap::find(treap, key);
			assert(x != NULL && x->key == key);
		}
	}
	t2 = clock() - t2;
	printf("Treap: %d ms\n", t2);
}
