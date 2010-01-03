#include <cstdio>
#include <algorithm>
using namespace std;

int seq[65536];

struct Node {
	int value;
	int low, mid, high;
	Node *l;	// [low, mid]
	Node *r;	// [mid+1, high]
	int sum, maxl, maxr, ans;
};

void update(Node *x)
{
	if (x->low == x->high) {
		// leaf
		x->sum = x->maxl = x->maxr = x->ans = x->value;
	} else {
		// split node
		x->sum = x->l->sum + x->r->sum;
		x->maxl = max(x->l->maxl, x->l->sum + x->r->maxl);
		x->maxr = max(x->r->maxr, x->r->sum + x->l->maxr);
		x->ans = max(x->l->maxr + x->r->maxl, max(x->l->ans, x->r->ans));
	}
}

Node *build(int a, int b)
{
	Node *x = new Node();
	x->low = a;
	x->high = b;
	x->mid = (a + b) / 2;
	if (a == b) {
		x->value = seq[a];
		x->l = x->r = NULL;
	} else {
		x->value = 0;
		x->l = build(a, x->mid);
		x->r = build(x->mid+1, b);
	}
	update(x);
	return x;
}

void modify(Node *root, int index, int newValue)
{
	if (root->low == root->high) {
		assert(root->low == index);
		root->value = newValue;
	} else if (index <= root->mid) {
		modify(root->l, index, newValue);
	} else {
		modify(root->r, index, newValue);
	}
	update(root);
}

int query(Node *root, int a, int b, int type)
{
	if (a < root->low) a = root->low;
	if (b > root->high) b = root->high;
	if (root->low == a && root->high == b) {
		if (type == 'a') return root->ans;
		if (type == 'l') return root->maxl;
		if (type == 'r') return root->maxr;
		if (type == 's') return root->sum;
	}
	if (b <= root->mid) return query(root->l, a, b, type);
	if (root->mid < a) return query(root->r, a, b, type);
	int res;
	if (type == 'a') {
		res = query(root->l, a, b, 'r') + query(root->r, a, b, 'l');
		res >?= query(root->l, a, b, 'a');
		res >?= query(root->r, a, b, 'a');
	} else if (type == 'l') {
		res = query(root->l, a, b, 'l');
		res >?= query(root->l, a, b, 's') + query(root->r, a, b, 'l');
	} else if (type == 'r') {
		res = query(root->r, a, b, 'r');
		res >?= query(root->r, a, b, 's') + query(root->l, a, b, 'r');
	} else {
		res = query(root->l, a, b, 's') + query(root->r, a, b, 's');
	}
	return res;
}

int main()
{
	int N, M;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &seq[i]);

	Node *root = build(1, N);

	scanf("%d", &M);
	for (int cs = 1; cs <= M; cs++) {
		int c, x, y;
		scanf(" %d %d %d", &c, &x, &y);

		if (c == 0) {
			modify(root, x, y);
		} else {
			printf("%d\n", query(root, x, y, 'a'));
		}
	}
}
