#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

struct pt { int x, y; };
bool operator <(pt p, pt q) { return p.y<q.y || (p.y==q.y && p.x<q.x); }
bool operator ==(pt p, pt q) { return p.x==q.x && p.y==q.y; }
int skew(pt a, pt b, pt c) { return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x); }

vector<pt> hull(vector<pt> p)
{
	if (p.size() <= 1) return p;

	sort(p.begin(), p.end());
	p.erase(unique(p.begin(), p.end()), p.end());

	int n = p.size(), k = 0;
	vector<pt> h;

	for (int i = 0; i < n; i++) {
		while (k >= 2 && skew(h[k-2], h[k-1], p[i]) <= 0)
			k--, h.pop_back();
		k++, h.push_back(p[i]);
	}

	int t = max(2,k+1);
	for (int i = n-2; i >= 0; i--) {
		while (k >= t && skew(h[k-2], h[k-1], p[i]) <= 0)
			k--, h.pop_back();
		k++, h.push_back(p[i]);
	}	

	return h;
}

int main()
{
	pt a[1024];
	int i, n, t;

	scanf("%d", &t);
	printf("%d\n", t);

	while (t-- > 0 && scanf("%d", &n) == 1) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &a[i].x, &a[i].y);
		scanf("%*d");

		vector<pt> h = hull(vector<pt>(a,a+n));

		printf("%d\n", h.size());
		for (i = 0; i < h.size(); i++)
			printf("%d %d\n", h[i].x, h[i].y);

		if (t > 0) printf("-1\n");
	}

	return 0;
}
