/*
ID: infnty1
LANG: C++
TASK: hotel
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

struct Node {
	int lo, hi, size;
	Node *left, *right;
	int status;
	int leftFree, rightFree, maxFree;

	int Size(int a, int b) {
		if (a < lo) a = lo;
		if (b > hi) b = hi;
		return a <= b ? (b - a + 1) : 0;
	}

	void propagate() {
		if (status != -1) {
			leftFree = rightFree = maxFree = (status == 0 ? size : 0);
			if (lo != hi) {
				left->status = right->status = status;
				status = -1;
			}
		}
	}
};

Node *make(int a, int b)
{
	Node *p = new Node();
	p->lo = a;
	p->hi = b;
	if (a == b) {
		p->left = p->right = NULL;
		p->status = 0;
	} else {
		p->status = -1;
		int c = (a + b) / 2;
		p->left = make(a, c);
		p->right = make(c+1, b);
	}
	p->leftFree = p->rightFree = p->maxFree = p->size = b - a + 1;
	return p;
}

void queryRange(Node *p, int a, int b, int &outL, int &outR, int &outM)
{
	if (a < p->lo) a = p->lo;
	if (b > p->hi) b = p->hi;

	p->propagate();

	if (a > b) {
		outL = outR = outM = 0;
	} else if (a == p->lo && b == p->hi) {
		outL = p->leftFree;
		outR = p->rightFree;
		outM = p->maxFree;
	} else {
		int LL, LR, LM, RL, RR, RM;
		queryRange(p->left, a, b, LL, LR, LM);
		queryRange(p->right, a, b, RL, RR, RM);

		outL = LL + (LL == p->left->Size(a,b) ? RL : 0);
		outR = RR + (RR == p->right->Size(a,b) ? LR : 0);
		outM = max(max(LM, RM), LR + RL);
	}
}

int queryRange(Node *p, int a, int b)
{
	int L = 0, R = 0, M = 0;
	queryRange(p, a, b, L, R, M);
	return M;
}

void updateRange(Node *p, int a, int b, int newValue)
{
	if (a < p->lo) a = p->lo;
	if (b > p->hi) b = p->hi;

	p->propagate();

	if (a > b) {
		;
	} else if (a == p->lo && b == p->hi) {
		p->status = newValue;
		p->propagate();
	} else {
		updateRange(p->left, a, b, newValue);
		updateRange(p->right, a, b, newValue);

		p->leftFree = p->left->leftFree;
		if (p->leftFree == p->left->size)
			p->leftFree += p->right->leftFree;

		p->rightFree = p->right->rightFree;
		if (p->rightFree == p->right->size)
			p->rightFree += p->left->rightFree;

		p->maxFree = max(p->left->maxFree, p->right->maxFree);
		p->maxFree = max(p->maxFree, p->left->rightFree + p->right->leftFree);
	}
}

int N;
Node *tree;

int checkin(int D)
{
	if (queryRange(tree, 1, N) < D) return 0;

	int left = D-1, right = N;
	while (right - left > 1) {
		int m = (left + right) / 2;
		if (queryRange(tree, 1, m) >= D)
			right = m;
		else
			left = m;
	}

	int r = right - D + 1;
	updateRange(tree, r, right, 1);

	return r;
}

void checkout(int X, int D)
{
	updateRange(tree, max(1, X), min(N, X + D - 1), 0);
}

int main()
{
	freopen("hotel.in", "r", stdin);
	freopen("hotel.out", "w", stdout);

	int Q, K, arg[10];
	scanf("%d %d", &N, &Q);

	tree = make(1, N);

	for (int i = 0; i < Q; i++) {
		scanf("%d", &K);
		for (int j = 0; j < K; j++) scanf("%d", &arg[j]);

		if (K == 1) {
			printf("%d\n", checkin(arg[0]));
		} else {
			checkout(arg[0], arg[1]);
		}
	}
}
