#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

template<typename T>
struct AVLNode {
	AVLNode<T> *left, *right, *parent;
	int size, height;
	T key;
};

// AVL tree.
// Notes: all keys must be unique; erase() invalidates iterators.
template<typename T> struct AVLTree {
	typedef AVLNode<T> Node;

	Node *root;
	static Node nil;

	static void update(Node *x) {
		x->size = x->left->size + 1 + x->right->size;
		x->height = 1 + max(x->left->height, x->right->height);
		x->left->parent = x;
		x->right->parent = x;
	}

	static Node *rotl(Node *x) {
		Node *y = x->right;
		x->right = y->left;
		y->left = x;
		update(x);
		update(y);
		return y;
	}

	static Node *rotr(Node *x) {
		Node *y = x->left;
		x->left = y->right;
		y->right = x;
		update(x);
		update(y);
		return y;
	}

	static Node *rebalance(Node *x) {
		update(x);
		if (x->left->height > 1 + x->right->height) {
			if (x->left->left->height < x->left->right->height)
				x->left = rotl(x->left);
			x = rotr(x);
		} else if (x->right->height > 1 + x->left->height) {
			if (x->right->right->height < x->right->left->height)
				x->right = rotr(x->right);
			x = rotl(x);
		}
		assert(abs(x->left->height - x->right->height) <= 1);
		return x;
	}

	static Node *insertNode(Node *x, Node *z) {
		if (x == &nil) {
			z->left = z->right = &nil;
			z->height = z->size = 1;
			return z;
		}

		if (z->key < x->key)
			x->left = insertNode(x->left, z);
		else
			x->right = insertNode(x->right, z);

		return rebalance(x);
	}

	static Node *remove(Node *x, const T &key) {
		if (x == &nil) {
			return &nil;
		} else if (key < x->key) {
			x->left = remove(x->left, key);
		} else if (x->key < key) {
			x->right = remove(x->right, key);
		} else {
			Node *y;
			if (x->left == &nil) { y = x->right; delete x; return y; }
			if (x->right == &nil) { y = x->left; delete x; return y; }
			for (y = x->right; y->left != &nil; y = y->left);
			x->key = y->key;
			x->right = remove(x->right, y->key);
		}
		return rebalance(x);
	}

	static void freeTree(Node *x) {
		if (x != &nil) {
			freeTree(x->left);
			freeTree(x->right);
			delete x;
		}
	}

	static Node *minimum(Node *x) {
		while (x->left != &nil) x = x->left;
		return x;
	}

	static Node *successor(Node *x) {
		if (x->right != &nil) {
			return minimum(x->right);
		} else {
			for (;;) {
				Node *y = x->parent;
				if (y == &nil || x == y->left) return y;
				x = y;
			}
		}
	}

	Node *find(const T &key) const {
		Node *x;
		for (x = root; x != &nil;) {
			if (key < x->key)
				x = x->left;
			else if (x->key < key)
				x = x->right;
			else
				break;
		}
		return x;
	}

	// Returns 0-based rank of given element
	int rank(Node *x) const {
		if (x == &nil) {
			return root->size;
		} else {
			Node *y = x->left;
			int k = y->size;
			for (; x != &nil; x = x->parent) {
				if (x->left != y) k += x->left->size + 1;
				y = x;
			}
			return k;
		}
	}

	// Returns iterator to k-th (0-based) smallest element
	Node *kth(int k) const {
		if (k >= root->size) return &nil;
		for (Node *x = root;;) {
			assert(x != &nil);
			if (k < x->left->size) {
				x = x->left;
			} else if (k == x->left->size) {
				return x;
			} else {
				k -= x->left->size + 1;
				x = x->right;
			}
		}
	}

	Node *insert(const T &key) {
		Node *x = new Node();
		x->key = key;
		root = insertNode(root, x);
		root->parent = &nil;
		return x;
	}

	void erase(const T &key) {
		root = remove(root, key);
		root->parent = &nil;
	}

	AVLTree() { root = &nil; nil.size = nil.height = 0; nil.parent = &nil; }
	~AVLTree() { freeTree(root); }
};

template<class T> AVLNode<T> AVLTree<T>::nil;

// STL-like interface for AVLTree
template<class T>
class AVLSet : private AVLTree<T> {
	typedef AVLNode<T> Node;

public:
	struct iterator {
		typedef forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef T &reference;
		typedef T *pointer;
		typedef ptrdiff_t difference_type;
		Node *x;
		iterator(Node *x_) : x(x_) { }
		bool operator ==(const iterator &i) const { return x == i.x; }
		bool operator !=(const iterator &i) const { return x != i.x; }
		T &operator *() const { return x->key; }
		void operator ++() { x = successor(x); }
	};

	iterator begin() const { return iterator(minimum(AVLTree<T>::root)); }
	iterator end() const { return iterator(&AVLTree<T>::nil); }
	iterator insert(const T &key) { return iterator(AVLTree<T>::insert(key)); }
	iterator find(const T &key) const { return iterator(AVLTree<T>::find(key)); }
	void erase(const T &key) { AVLTree<T>::erase(key); }
	void erase(iterator it) { AVLTree<T>::erase(it.x->key); }
	int size() const { return AVLTree<T>::root->size; }
	bool empty() const { return size() == 0; }
	int rank(iterator it) const { return AVLTree<T>::rank(it.x); }
	iterator kth(int k) const { return iterator(AVLTree<T>::kth(k)); }
};

#include <set>
int main()
{
	AVLSet<int> tree;
	set<int> stl_tree;

	srand(42);

	for (int t = 0; t < 10000; t++) {
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
			AVLSet<int>::iterator it = tree.kth(k);
			AVLSet<int>::iterator it2 = tree.find(v1[k]);
			assert(it == it2);
			assert(*it == v1[k]);
			assert(tree.rank(it) == k);
//			printf("erasing %d\n", *it);
			tree.erase(it);
			stl_tree.erase(v1[k]);
		}
//		tree.verify();
	}

	printf("OK\n");
}
