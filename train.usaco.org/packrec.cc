/*
ID: infnty1
PROB: packrec
LANG: C++
*/
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

struct pt { int x, y; };
bool operator <(const pt &a, const pt &b) { return a.x<b.x || (a.x==b.x && a.y<b.y); }
bool operator ==(const pt &a, const pt &b) { return a.x==b.x && a.y==b.y; }

vector<pt> sol;

pt make(int x, int y) { pt p={x,y}; return p; }
pt T(pt p) { return make(p.y,p.x); }
int area(pt p) { return p.x*p.y; }

void add(pt b)
{
	if (b.y < b.x) swap(b.x, b.y);
	if (!sol.empty()) {
		if (area(sol[0]) < area(b)) return;
		if (area(sol[0]) > area(b)) sol.clear();
	}
	sol.push_back(b);
}

void add(int x, int y) { add(make(x,y)); }

void go(pt a, pt b, pt c, pt d)
{
	add(a.x + b.x + c.x + d.x, a.y >? b.y >? c.y >? d.y);
	add(a.x >? b.x >? c.x >? d.x, a.y + b.y + c.y + d.y);

	add(a.x >? (b.x + c.x + d.x), a.y + (b.y >? c.y >? d.y));

	add(a.x + (b.x >? (c.x + d.x)), a.y >? (b.y + (c.y >? d.y)));

	add(a.x + (b.x >? c.x) + d.x, a.y >? (b.y + c.y) >? d.y);

	add(a.x + b.x + (c.x >? d.x), a.y >? b.y >? (c.y + d.y));

	if (b.x+d.x <= a.x+c.x &&
	    (b.x <= a.x || a.y >= c.y) &&
	    (d.x <= c.x || a.y <= c.y))
		add(a.x+c.x, (a.y + b.y) >? (c.y + d.y));

}

int main()
{
	vector<pt> v(4);

	freopen("packrec.in", "r", stdin);
	freopen("packrec.out", "w", stdout);

	for (int i = 0; i < 4; i++)
		scanf("%d %d", &v[i].x, &v[i].y);

	sort(v.begin(), v.end());
	do {
		for (int z = 0; z < 16; z++) {
			vector<pt> w(v);
			for (int i = 0; i < 4; i++)
				if (z & (1 << i)) w[i] = T(w[i]);
			go(w[0], w[1], w[2], w[3]);
		}
	} while (next_permutation(v.begin(), v.end()));

	printf("%d\n", area(sol[0]));
	sort(sol.begin(), sol.end());
	sol.erase(unique(sol.begin(), sol.end()), sol.end());

	for (int i = 0; i < sol.size(); i++)
		printf("%d %d\n", sol[i].x, sol[i].y);

	return 0;
}
