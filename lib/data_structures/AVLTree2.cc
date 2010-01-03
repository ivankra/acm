// A simple implementation of AVL tree.
#include <algorithm>
using namespace std;

struct Node *nil = 0;

struct Node {
	Node *l, *r;
	int h, size, key;
	Node(int k) : l(nil), r(nil), h(1), size(1), key(k) {}
	void u() { h = 1 + max(l->h, r->h); size = l->size + 1 + r->size; }
};

Node *create() { if(nil==0){nil=new Node(0);nil->h=nil->size=0;} return nil; }
void destroy(Node *x) { if(x!=nil){destroy(x->l); destroy(x->r); delete x;} }

Node *rotl(Node *x) { Node *y=x->r; x->r=y->l; y->l=x; x->u(); y->u(); return y; }
Node *rotr(Node *x) { Node *y=x->l; x->l=y->r; y->r=x; x->u(); y->u(); return y; }

Node *rebalance(Node *x) {
	x->u();
	if (x->l->h > 1 + x->r->h) {
		if (x->l->l->h < x->l->r->h) x->l = rotl(x->l);
		x = rotr(x);
	} else if (x->r->h > 1 + x->l->h) {
		if (x->r->r->h < x->r->l->h) x->r = rotr(x->r);
		x = rotl(x);
	}
	return x;
}

Node *insert(Node *x, int key) {
	if (x == nil) return new Node(key);
	if (key < x->key) x->l = insert(x->l, key); else x->r = insert(x->r, key);
	return rebalance(x);
}

Node *remove(Node *x, int key) {
	if (x == nil) return nil;
	if (key < x->key) x->l = remove(x->l, key);
	else if (x->key < key) x->r = remove(x->r, key);
	else {
		Node *y;
		if (x->l == nil) { y = x->r; delete x; return y; }
		if (x->r == nil) { y = x->l; delete x; return y; }
		for (y = x->r; y->l != nil; y = y->l);
		x->key = y->key;
		x->r = remove(x->r, y->key);
	}
	return rebalance(x);
}

Node *find(Node *x, int key) {
	if (x == nil) return nil;
	if (key < x->key) return find(x->l, key);
	if (x->key < key) return find(x->r, key);
	return x;
}

Node *kth(Node *x, int k) {
	if (k < 0 || k >= x->size) return nil;
	if (k < x->l->size) return kth(x->l, k);
	k -= x->l->size + 1;
	return k < 0 ? x : kth(x->r, k);
}

int rank(Node *x, int key) {
	if (x == nil) return 0;
	if (key < x->key) return rank(x->l, key);
	return x->l->size + (x->key < key ? 1 + rank(x->r, key) : 0);
}
