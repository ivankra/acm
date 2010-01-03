// Treap - a randomized binary search tree.
// Each node in the tree has an additional field ('aux' in this implementation),
// with respect to which it satisfies a min-heap property.
// When this field is assigned a unique random value, permutation of
// these values uniquely defines shapes of the tree, so the expected
// height is O(log n).
#include <algorithm>
#include <vector>
#include <sstream>
#include <cmath>
#include <cassert>
#include <set>
using namespace std;

struct Node *nil = NULL;

struct Node {
	int key, aux, size;  Node *l, *r;
	Node(int k) : key(k), aux(rand()), size(1), l(nil), r(nil) { }
};

Node *create_tree() {
	if (nil == NULL) {
		nil = new Node(0);
		nil->size = 0; nil->aux = 0x7fffffff;
		nil->l = nil->r = nil;
	}
	return nil;
}

void destroy_tree(Node *x) {
	if (x != nil) { destroy_tree(x->l); destroy_tree(x->r); delete x; }
}

Node *upd(Node *p) { if (p != nil) p->size = 1 + p->l->size + p->r->size; return p; }

void split(Node *p, Node *by, Node **L, Node **R) {
	if (p == nil) { *L = *R = nil; }
	else if (p->key < by->key) { split(p->r, by, &p->r, R); *L = upd(p); }
	else { split(p->l, by, L, &p->l); *R = upd(p); }
}

Node *insert(Node *p, Node *n) {
	if (p == nil) return upd(n);
	if (n->aux <= p->aux) { split(p, n, &n->l, &n->r); return upd(n); }
	if (n->key < p->key) p->l = insert(p->l, n); else p->r = insert(p->r, n);
	return upd(p);
}

Node *merge(Node *L, Node *R) {
	Node *p;
	if (L == nil || R == nil) p = (L != nil ? L : R);
	else if (L->aux < R->aux) { L->r = merge(L->r, R); p = L; }
	else { R->l = merge(L, R->l); p = R; }
	return upd(p);
}

Node *remove(Node *p, int key) {
	if (p == nil) return nil;
	if (key == p->key) { Node *q = merge(p->l, p->r); delete p; return upd(q); }
	if (key < p->key) p->l = remove(p->l, key); else p->r = remove(p->r, key);
	return upd(p);
}

// Finds node by key.
Node *find(Node *x, int key) {
	if (x == nil) return nil;
	if (key < x->key) return find(x->l, key);
	if (x->key < key) return find(x->r, key);
	return x;
}

Node *find_kth(Node *p, int k) {
	if (k < 0 || k >= p->size) return nil;
	for (;;) {
		if (k < p->l->size) {
			p = p->l;
		} else {
			if ((k -= p->l->size + 1) < 0) return p;
			p = p->r;
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
