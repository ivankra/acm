#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

struct Node {
	int a, b;
	Node *left, *right;
	int minVal, minCount, lazy;
};

Node *build(int a, int b)
{
	Node *p = new Node();
	p->a = a;
	p->b = b;
	p->minVal = 0;
	p->minCount = b - a + 1;
	p->lazy = 0;
	if (a != b) {
		int mid = (a + b) / 2;
		p->left = build(a, mid);
		p->right = build(mid+1, b);
	}
	return p;
}

void increase(Node *p, int a, int b, int by)
{
	if (a < p->a) a = p->a;
	if (b > p->b) b = p->b;
	if (a > b) return;

	if (p->a == p->b) {
		p->minVal += by + p->lazy;
		p->lazy = 0;
	} else if (a == p->a && b == p->b) {
		p->lazy += by;
	} else {
		p->left->lazy += p->lazy;
		p->right->lazy += p->lazy;
		p->lazy = 0;
		increase(p->left, a, b, by);
		increase(p->right, a, b, by);

		int lv = p->left->minVal + p->left->lazy;
		int rv = p->right->minVal + p->right->lazy;
		p->minVal = min(lv, rv);
		p->minCount = 0;
		if (lv == p->minVal) p->minCount += p->left->minCount;
		if (rv == p->minVal) p->minCount += p->right->minCount;
	}
}

struct Event {
	int x, s, y1, y2;
	Event(int x_, int s_, int y1_, int y2_) : x(x_), s(s_), y1(y1_), y2(y2_) {}
	bool operator <(const Event &e) const {
		if (x != e.x) return x < e.x;
		return s > e.s;
	}
};

int main()
{
	freopen("area.in", "r", stdin);
	freopen("area.out", "w", stdout);

	int N;
	scanf("%d", &N);

	vector<Event> events;

	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);

		if (x1 == x2 || y1 == y2) continue;

		events.push_back(Event(x1, +1, y1, y2));
		events.push_back(Event(x2, -1, y1, y2));
	}

	sort(events.begin(), events.end());

	Node *root = build(0, 10010);
	int at = 0, area = 0;

	for (int i = 0; i < (int)events.size(); i++) {
		const Event &e = events[i];
		if (e.x != at) {
			int nonzero = (root->b - root->a + 1) - root->minCount;
			area += (e.x - at) * nonzero;
			at = e.x;
		}
		increase(root, e.y1, e.y2-1, e.s);
	}

	printf("%d\n", area);
}
