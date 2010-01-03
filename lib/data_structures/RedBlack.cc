#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

// Red-black tree.
//
// Supports order statistic queries.
//
// Type T must overload operator < for comparison,
// and have a public default and copy constructor.
//
// Reference: Cormen et al. Introduction to Algorithms, 2nd Edition.
// MIT Press, 2001.  Chapter 13. "Red-Black Trees".
template<typename T>
class RBTree {
	struct Node {
		Node *left, *right, *parent;
		int size;
		bool red;
		T key;
		Node(const T &k) : key(k) { }
	};

	Node *nil, *root;

	void freeTree(Node *x) {
		if (x != nil) {
			freeTree(x->left);
			freeTree(x->right);
			delete x;
		}
	}

	Node *minimum(Node *x) const {
		while (x->left != nil) x = x->left;
		return x;
	}

	Node *successor(Node *x) const {
		if (x->right != nil) {
			return minimum(x->right);
		} else {
			for (;;) {
				Node *y = x->parent;
				if (y == nil || x == y->left) return y;
				x = y;
			}
		}
	}

	void rightRotate(Node *x) {
		Node *y = x->left;
		x->left = y->right;
		if (x->left != nil)
			x->left->parent = x;

		y->parent = x->parent;
		if (x->parent == nil)
			root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;

		y->right = x;
		x->parent = y;

		x->size = x->left->size + 1 + x->right->size;
		y->size = y->left->size + 1 + y->right->size;
	}

	void leftRotate(Node *x) {
		Node *y = x->right;
		x->right = y->left;
		if (x->right != nil)
			x->right->parent = x;

		y->parent = x->parent;
		if (x->parent == nil)
			root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;

		y->left = x;
		x->parent = y;

		x->size = x->left->size + 1 + x->right->size;
		y->size = y->left->size + 1 + y->right->size;
	}

	Node *insertNode(Node *z) {
		Node *x, *y;
		for (x = root, y = nil; x != nil;) {
			x->size++;
			y = x;
			x = z->key < y->key ? y->left : y->right;
		}

		z->left = z->right = nil;
		z->size = 1;
		z->red = true;
		z->parent = y;
		if (y == nil)
			root = z;
		else if (z->key < y->key)
			y->left = z;
		else
			y->right = z;

		insertFixUp(z);
		return z;
	}

	void insertFixUp(Node *z) {
		Node *p, *g, *y;
		while (true) {
			p = z->parent;
			if (!p->red) break;

			g = p->parent;
			if (g->left == p) {
				y = g->right;
				if (!y->red) {
					// black uncle
					if (z == p->right) {
						// double-rotation case
						leftRotate(p);
						swap(p, z);
					}
					rightRotate(g);
					g->red = true;
					p->red = false;
					break;
				}
			} else {
				// symmetrical cases
				y = g->left;
				if (!y->red) {
					if (z == p->left) {
						rightRotate(p);
						swap(p, z);
					}
					leftRotate(g);
					g->red = true;
					p->red = false;
					break;
				}
			}

			// red uncle
			p->red = false; y->red = false; g->red = true;
			z = g;
		}

		root->red = false;
	}

	void deleteNode(Node *z) {
		assert(z != nil);
		Node *y = (z->left == nil || z->right == nil) ? z : successor(z);
		Node *x = (y->left != nil ? y->left : y->right);

		// splice out y
		x->parent = y->parent;
		if (y->parent == nil)
			root = x;
		else if (y->parent->left == y)
			y->parent->left = x;
		else
			y->parent->right = x;

		bool y_red = y->red;

		if (y != z) {
			// re-link y in place of z
			y->left = z->left;
			if (z->left != nil) z->left->parent = y;
			y->right = z->right;
			if (z->right != nil) z->right->parent = y;
			y->parent = z->parent;
			if (z->parent == nil)
				root = y;
			else if (z->parent->left == z)
				z->parent->left = y;
			else
				z->parent->right = y;
			y->red = z->red;
			if (x->parent == z) x->parent = y;
		}
		delete z;

		// Update 'size' fields
		for (z = x->parent; z != nil; z = z->parent)
			z->size = z->left->size + 1 + z->right->size;

		if (!y_red) {
			deleteFixUp(x);
		}
	}

	void deleteFixUp(Node *x) {
		Node *p, *w;
		while (x != root && !x->red) {
			p = x->parent;
			if (p->left == x) {
				w = p->right;
				if (w->red) {
					// Case 1: x's sibling w is red.  Make x's sibling black.
					w->red = false;
					p->red = true;
					leftRotate(p);
				} else if (!w->left->red && !w->right->red) {
					// Case 2: w is black, and both its children are black.
					// Recolor, and move up the tree.
					w->red = true;
					x = p;
				} else {
					if (!w->right->red) {
						// Case 3: left w's child is red, right w's child is black
						rightRotate(w);
						w = p->right;
					}

					// Case 4: right w's child is red
					w->red = p->red;
					p->red = false;
					w->right->red = false;
					leftRotate(p);
					x = root;
				}
			} else {
				// Symmetrical cases
				w = p->left;
				if (w->red) {
					w->red = false;
					p->red = true;
					rightRotate(p);
				} else if (!w->left->red && !w->right->red) {
					w->red = true;
					x = p;
				} else {
					if (!w->left->red) {
						leftRotate(w);
						w = p->left;
					}
					w->red = p->red;
					p->red = false;
					w->left->red = false;
					rightRotate(p);
					x = root;
				}
			}
		}

		x->red = false;
	}

	RBTree(const RBTree &) {}
	void operator =(const RBTree &) {}

public:
	RBTree() {
		nil = new Node(T());
		nil->red = false;
		nil->size = 0;
		root = nil;
	}

	~RBTree() {
		freeTree(root);
		delete nil;
	}

	typedef T value_type;

	struct iterator {
		typedef forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef T &reference;
		typedef T *pointer;
		typedef ptrdiff_t difference_type;
		Node *node;
		RBTree *tree;
		iterator(Node *x, RBTree *t) : node(x), tree(t) {}
		void operator ++() { node = tree->successor(node); }
		T &operator *() const { return node->key; }
		bool operator ==(const iterator &it) const { return node == it.node; }
		bool operator !=(const iterator &it) const { return node != it.node; }
	};

	iterator begin() { return iterator(minimum(root), this); }
	iterator end() { return iterator(nil, this); }
	int size() const { return root->size; }
	bool empty() const { return root == nil; }
	iterator insert(const T &key) { return iterator(insertNode(new Node(key)), this); }
	void erase(iterator it) { deleteNode(it.node); }
	void clear() { freeTree(root); root = nil; }

	iterator find(const T &key) {
		Node *x = root;
		while (x != nil) {
			if (key < x->key)
				x = x->left;
			else if (x->key < key)
				x = x->right;
			else
				return iterator(x, this);
		}
		return end();
	}

	// Returns 0-based rank of given element
	int rank(iterator it) const {
		Node *x = it.node;
		if (x == nil) {
			return size();
		} else {
			Node *y = x->left;
			int k = y->size;
			for (; x != nil; x = x->parent) {
				if (x->left != y) k += x->left->size + 1;
				y = x;
			}
			return k;
		}
	}

	// Returns iterator to k-th (0-based) smallest element
	iterator kth(int k) {
		if (k >= size()) return end();
		for (Node *x = root;;) {
			assert(x != nil);
			if (k < x->left->size) {
				x = x->left;
			} else if (k == x->left->size) {
				return iterator(x, this);
			} else {
				k -= x->left->size + 1;
				x = x->right;
			}
		}
	}

	// Verifies tree's invariants.
	void verify() {
		assert(!nil->red && nil->size == 0 && !root->red);
		assert(root->parent == nil);
		verifyTree(root);
	}

//--- TEST CODE---

	// Dumps tree's structure in XML
	void dump(ostream &o, Node *x = NULL, int indent = 0) {
		if (x == NULL) {
			o << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<rbtree>\n";
			dump(o, root, 1);
			o << "</rbtree>\n";
		} else if (x != nil) {
			o << string(indent*2, ' ') << "<node key=\"" << x->key <<
				"\" color=\"" << (x->red ? "red" : "black") <<
				"\" size=\"" << x->size << "\"";
			if (x->left == nil && x->right == nil) {
				o << " />\n";
			} else {
				o << ">\n";
				dump(o, x->left, indent+1);
				dump(o, x->right, indent+1);
				o << string(indent*2, ' ') << "</node>\n";
			}
		}
	}

private:
	// Verifies red-black tree invariants in x's subtree. Returns black-height of x.
	int verifyTree(Node *x) {
		if (x == nil) return 0;
		if (x->red) assert(!x->left->red && !x->right->red);
		if (x->left != nil) {
			assert(x->left->parent == x);
			assert(!(x->key < x->left->key));
		}
		if (x->right != nil) {
			assert(x->right->parent == x);
			assert(!(x->right->key < x->key));
		}
		int h1 = verifyTree(x->left);
		int h2 = verifyTree(x->right);
		assert(h1 == h2);
		assert(x->size == x->left->size + 1 + x->right->size);
		return h1 + (x->red ? 0 : 1);
	}
};

#if 1
#include <set>
int main()
{
	RBTree<int> tree;
	set<int> stl_tree;

	srand(42);

	for (int i = 0; i < 10000; i++) {
		assert(tree.size() == (int)stl_tree.size());
		if (rand() % 100 < 50 || tree.size() < 500) {
			int key;
			do { key = rand(); } while (stl_tree.count(key) > 0);
//			printf("inserting %d\n", key);
			tree.insert(key);
			stl_tree.insert(key);
		} else {
			vector<int> v1(tree.begin(), tree.end());
			vector<int> v2(stl_tree.begin(), stl_tree.end());
			assert(v1 == v2);
			int k = rand() % tree.size();
			RBTree<int>::iterator it = tree.kth(k);
			RBTree<int>::iterator it2 = tree.find(v1[k]);
			assert(it == it2);
			assert(*it == v1[k]);
			assert(tree.rank(it) == k);
//			printf("erasing %d\n", *it);
			tree.erase(it);
			stl_tree.erase(v1[k]);
		}
		tree.verify();
	}

	printf("OK\n");
}
#endif
