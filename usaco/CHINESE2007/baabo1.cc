/*
ID: infnty1
LANG: C++
TASK: baabo
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
#define foreach(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
const long long NINF = -(1LL << 61);

/*struct Node {
	Node *left, *right, *parent;
	int aux;

	int m;
	long long b;
	double start;

	double end() const { return right == NULL ? 2000000.0 : right->start; }
};

Node memory[1024*1024], *freelist = NULL;

double xintersect(Node *p, Node *q) {
	if (p->m == q->m) return -1;
	return (q->b - p->b) / (double)(p->m - q->m);
}

Node *rotl(Node *x) {
	Node *y = x->right;
	x->right = y->left;
	if (y->left != NULL) y->left->parent = x;
	y->parent = NULL;
	y->left = x;
	x->parent = y;
	return y;
}

Node *rotr(Node *x) {
	Node *y = x->left;
	x->left = y->right;
	if (y->right != NULL) y->right->parent = x;
	y->parent = NULL;
	y->right = x;
	x->parent = y;
	return y;
}

Node *alloc() {
	assert(freelist != NULL);
	Node *p = freelist;
	freelist = freelist->left;
	p->left = p->right = NULL;
	p->aux = rand();
	return p;
}

void deallocNode(Node *p) {
	p->left = freelist;
	freelist = p;
}

void deallocTree(Node *p) {
	if (p != NULL) {
		deallocTree(p->left);
		deallocTree(p->right);
		deallocNode(p);
	}
}

Node *insert(Node *root, Node *newNode, double startBound)
{
	if (root == NULL) {
		newNode->start = startBound;
		return newNode;
	}

	if (root->m == newNode->m && newNode->b <= root->b) {
		deallocNode(newNode);
		return root;
	}

	double x = xintersect(root, newNode);
	if (x < root->start + 1e-12) {
		root->left = insert(root->left, newNode, startBound);
		root->left->parent = root;
		if (root->left->aux < root->aux)
			root = rotr(root);
	} else {
		root->right = insert(root->right, newNode, max(x, root->start));
		root->right->parent = root;
		if (root->right->aux < root->aux)
			root = rotl(root);
	}
	return root;
}

Node *successor(Node *p) {
	if (p == NULL) return NULL;
	if (p->right != NULL) {
		p = p->right;
		while (p->left != NULL)
			p = p->left;
		return p;
	} else {
		while (p->parent != NULL) {
			if (p->parent->left == p)
				return p->parent;
			p = p->parent;
		}
		return NULL;
	}
}
*/

// y = mx + b
// N<=1001,  0<=m<=10^6, |b|<=10^12, 0<=x<=2*10^6,  |y|<=3*10^12
struct Maximizer {
	int N, m[1001];
	long long b[1001];

	Maximizer() { N = 0; }
	void clear() { N = 0; }

	void add(long long mi, long long bi) {
		m[N] = mi;
		b[N] = bi;
		N++;
	}
/*		Node *p = alloc();
		p->m = mi;
		p->b = bi;
		root = insert(root, p, 0.0);
		root->parent = NULL;

		while (true) {
			Node *q = successor(p);
			if (q == NULL) break;

			double x = xintersect(p, q);
			...
		}*/

	long long eval(int x) const {
		long long res = m[0] * (long long)x + b[0];
		for (int i = 1; i < N; i++) {
			long long y = m[i] * (long long)x + b[i];
			if (y > res) res = y;
		}
		return res;
	}
};

static inline long long sqr(long long x) { return x * x; }

int main()
{
	static int N, A[1024], B[1024];
	static long long SA[1024], SB[1024], f00_prev[1024], f00_cur[1024];
	static Maximizer m00[1001], m10;

	freopen("baabo.in", "r", stdin);
	freopen("baabo.out", "w", stdout);

	srand(108525234);

	/*{
		int K = sizeof(memory) / sizeof(memory[0]);
		for (int i = 0; i < K; i++)
			memory[i].left = &memory[i+1];
		memory[K-1].left = NULL;
		freelist = &memory[0];
	}*/

	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", &A[i]);
	for (int i = 0; i < N; i++) scanf("%d", &B[i]);

	SA[0] = 0;
	for (int i = 1; i <= N; i++) SA[i] = SA[i-1] + A[i-1];
	SB[0] = 0;
	for (int i = 1; i <= N; i++) SB[i] = SB[i-1] + B[i-1];

	for (int i = 0; i <= N; i++) f00_prev[i] = -sqr(SB[N] - SB[i]);
	for (int j = 0; j < N; j++) m00[j].add(SA[N], -sqr(SA[N]));

	for (int i = N-1; i >= 0; i--) {
		m10.clear();
		m10.add(SB[N], -sqr(SB[N]));

		f00_cur[N] = -sqr(SA[N] - SA[i]);

		for (int j = N-1; j >= 0; j--) {
			long long f11 = A[i] * B[j] + f00_prev[j+1];

			m10.add(SB[j], f11 - sqr(SB[j]));
			long long f10 = m10.eval(2*SB[j]) - sqr(SB[j]);

			m00[j].add(SA[i], f10 - sqr(SA[i]));
			f00_cur[j] = m00[j].eval(2*SA[i]) - sqr(SA[i]);
		}

		for (int j = 0; j <= N; j++)
			f00_prev[j] = f00_cur[j];
	}

	printf("%lld\n", f00_cur[0]);

	return 0;
}
