#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

struct Node {
	Node *left, *right, *parent;
	int aux;

	int a, b, b_max, r;

	bool operator <(const Node &o) const {
		return a < o.a;
	}

	Node(int A, int B, int R) {
		a = A;
		b = b_max = B;
		r = R;
		aux = rand();
		left = right = parent = NULL;
	}

	void update() {
		parent = NULL;
		b_max = b;
		if (left != NULL) { left->parent = this; b_max = max(b_max, left->b_max); }
		if (right != NULL) { right->parent = this; b_max = max(b_max, right->b_max); }
	}
};

void split(Node *p, Node *mid, Node **l, Node **r) {
	if (p == NULL) { *l = *r = NULL; }
	else if (!(*mid < *p)) { split(p->right, mid, &p->right, r); p->update(); *l = p; }
	else { split(p->left, mid, l, &p->left); p->update(); *r = p; }
}

Node *merge(Node *p, Node *q) {
	if (p == NULL || q == NULL) {
		if (p != NULL) { p->update(); return p; }
		if (q != NULL) { q->update(); return q; }
		return NULL;
	}
	if (p->aux < q->aux) { p->right = merge(p->right, q); p->update(); return p; }
	q->left = merge(p, q->left); q->update(); return q;
}

Node *insert(Node *p, Node *n) {
	if (p == NULL) { n->update(); return n; }
	if (n->aux < p->aux) { split(p, n, &n->left, &n->right); n->update(); return n; }
	if (!(*p < *n))
		p->left = insert(p->left, n);
	else
		p->right = insert(p->right, n);
	p->update();
	return p;
}

Node *remove(Node *p) {
	if (p == NULL) return NULL;

	Node *q = merge(p->left, p->right);
	Node *u = p->parent;
	if (u != NULL) {
		if (u->left == p) u->left = q; else u->right = q;
	}
	delete p;
	p = q;

	while (u != NULL) { p = u; u = p->parent; p->update(); }
	return p;
}


struct Rect {
	int x1, y1, x2, y2, up;
	long long area, visible;
	Node *node;
};

struct Event {
	int x, i, r;
	Event(int X, int I, int R) : x(X), i(I), r(R) {}
	bool operator <(const Event &e) const {
		if (x != e.x) return x < e.x;
		return i < e.i;
	}
};

int main()
{
	Rect *R;
	int N;

	scanf("%d", &N);
	N++;
	R = new Rect[N];

	R[0].x1 = R[0].y1 = 0;
	scanf("%d %d", &R[0].x2, &R[0].y2);

	for (int i = 1; i < N; i++) {
		scanf("%d %d %d %d", &R[i].x1, &R[i].y1, &R[i].x2, &R[i].y2);
		if (R[i].x1 > R[i].x2) swap(R[i].x1, R[i].x2);
		if (R[i].y1 > R[i].y2) swap(R[i].y1, R[i].y2);
	}

	for (int i = 0; i < N; i++) {
		R[i].up = -1;
		R[i].node = NULL;
		R[i].area = (R[i].x2-(long long)R[i].x1) * (R[i].y2-(long long)R[i].y1);
		R[i].visible = R[i].area;
	}

	R[0].node = new Node(R[0].y1, R[0].y2, 0);
	Node *tree = insert(NULL, R[0].node);

	vector<Event> eq;
	for (int i = 1; i < N; i++) {
		eq.push_back(Event(R[i].x1, +1, i));
		eq.push_back(Event(R[i].x2, -1, i));
	}
	sort(eq.begin(), eq.end());

	for (int i = 0; i < (int)eq.size(); i++) {
		const Event &e = eq[i];
		Rect &r = R[e.r];

		if (e.i > 0) {
			r.node = new Node(r.y1, r.y2, e.r);
			tree = insert(tree, r.node);

			Node *p = r.node;
			for (;;) {
				if (p->b > r.y2) break;
				if (p->left != NULL && p->left->b_max > r.y2) break;

				for (;;) {
					Node *q = p->parent;
					assert(q != NULL);
					if (q->right == p) { p = q; break; }
					p = q;
				}
			}

			if (p->b <= r.y2) {
				assert(p->left != NULL);
				p = p->left;
				for (;;) {
					if (p->right != NULL && p->right->b_max > r.y2)
						p = p->right;
					else if (p->b > r.y2)
						break;
					else if (p->left != NULL && p->left->b_max > r.y2)
						p = p->left;
					else
						assert(0 == 1);
				}
			}

			r.up = p->r;
			R[r.up].visible -= r.area;
		} else {
			tree = remove(r.node);
			r.node = NULL;
		}

	}

	vector<long long> res;
	for (int i = 0; i < N; i++)
		if (R[i].visible > 0) res.push_back(R[i].visible);
	sort(res.begin(), res.end());

	for (int i = 0; i < (int)res.size(); i++)
		printf(i==0 ? "%I64d" : " %I64d", res[i]);
	printf("\n");
}
