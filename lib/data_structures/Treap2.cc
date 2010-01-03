#include <algorithm>
using namespace std;

typedef int key_type;

struct Node *nil = NULL;

struct Node {
	Node *l, *r;
	int aux, size;
	key_type key;
	void u() { size = l->size + 1 + r->size; }
	Node(const key_type &k) : l(nil), r(nil), aux(rand()), size(1), key(k) { }
};

Node *create_tree() {
	if (nil == NULL) { nil = new Node(key_type()); nil->size = 0; nil->aux = 0x7fffffff; }
	return nil;
}

void destroy_tree(Node *x) {
	if (x != nil) { destroy_tree(x->l); destroy_tree(x->r); delete x; }
}

Node *rotl(Node *x) { Node *y=x->r; x->r=y->l; y->l=x; x->u(); y->u(); return y; }
Node *rotr(Node *x) { Node *y=x->l; x->l=y->r; y->r=x; x->u(); y->u(); return y; }

Node *insert(Node *x, Node *z) {
	if (x == nil) return z;
	if (z->key < x->key) {
		x->l = insert(x->l, z); x->u();
		if (x->l->aux < x->aux) x = rotr(x);
	} else {
		x->r = insert(x->r, z); x->u();
		if (x->r->aux < x->aux) x = rotl(x);
	}
	return x;
}

Node *remove(Node *x, const key_type &key) {
	if (x == nil) return x;
	if (key < x->key) {
		x->l = remove(x->l, key);
	} else if (x->key < key) {
		x->r = remove(x->r, key);
	} else {
		Node *y;
		if (x->l == nil) { y = x->r; delete x; return y; }
		if (x->r == nil) { y = x->l; delete x; return y; }
		for (y = x->r; y->l != nil; y = y->l);
		x->key = y->key;
		x->r = remove(x->r, x->key);
	}
	x->u();
	return x;
}


// Finds node by key.
Node *find(Node *x, const key_type &key) {
	if (x == nil) return nil;
	if (key < x->key) return find(x->l, key);
	if (x->key < key) return find(x->r, key);
	return x;
}

// Returns (k-1)-th smallest element
Node *find_kth(Node *x, int k) {
	if (k < 0 || k >= x->size) return nil;
	for (;;) {
		if (k < x->l->size) {
			x = x->l;
		} else {
			if ((k -= x->l->size + 1) < 0) return x;
			x = x->r;
		}
	}
}


// --- TEST CODE ---

#include <cstdio>
#include <cassert>
#include <vector>
#include <set>

void traverse(Node *x, vector<int> &out) {
	if (x != nil) {
		assert(x->aux <= x->l->aux && x->aux <= x->r->aux);		
		assert(x->size == x->l->size + 1 + x->r->size);
		traverse(x->l, out);
		out.push_back(x->key);
		traverse(x->r, out);
	}
}

int main()
{
	Node *tree = create_tree();

	srand(42);
	set<int> stl;

	for (int t = 0; t < 50000; t++) {
		if (rand() % 100 < 50 || stl.size() < 500) {
			int key;
			do { key = rand() % 1000000; } while (stl.count(key) > 0);
			stl.insert(key);
			tree = insert(tree, new Node(key));
		}

		vector<int> v1, v2(stl.begin(), stl.end());
		traverse(tree, v1);
		assert(v1 == v2);

		if (rand() % 100 < 50 && v1.size() > 500) {
			int k = rand() % v1.size();
			int key = v1[k];
			Node *x = find(tree, key);
			assert(x != nil && x->key == key);
			assert(x == find_kth(tree, k));
			stl.erase(key);
			tree = remove(tree, key);
		}
	}

	destroy_tree(tree);

	printf("OK\n");
}
