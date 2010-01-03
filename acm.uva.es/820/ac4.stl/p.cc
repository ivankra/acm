#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

struct edge {
	int x, y, c, r;
};

vector<edge> E;
VVI G;

int flow(int s, int t) {
	for (int f = 0;;) {
		VI prev(G.size(), -1);
		queue<int> q;

		q.push(s); prev[s] = 0;
		while (!q.empty() && prev[t] < 0) {
			int x = q.front(); q.pop();
			for (int i = 0; i < (int)G[x].size(); i++) {
				int e = G[x][i], y = E[e].y;
				if (E[e].c == 0 || prev[y] >= 0) continue;
				prev[y] = e;
				q.push(y);
			}
		}

		if (prev[t] < 0)
			return f;

		int c = 0x7fffffff;
		for (int x = t; x != s; x = E[prev[x]].x)
			c <?= E[prev[x]].c;

		for (int x = t; x != s; x = E[prev[x]].x) {
			E[prev[x]].c -= c;
			E[E[prev[x]].r].c += c;
		}
		f += c;
	}
}

void add(int x, int y, int c) {
	struct edge e;
	e.x = x; e.y = y; e.c = c;
	e.r = E.size()+1;
	G[x].push_back(E.size());
	E.push_back(e);
	swap(e.x, e.y);
	e.r = E.size()-1;
	e.c = c;
	G[y].push_back(E.size());
	E.push_back(e);
}

int main()
{
	int w, c, x, y, z, n, s, t;

	for (w = 1; scanf("%d %d %d %d", &n, &s, &t, &c) == 4 && n > 0; w++) {
		E.clear();
		G = VVI(n+1, VI());

		while (c-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3)
			add(x, y, z);

		printf("Network %d\nThe bandwidth is %d.\n\n", w, flow(s, t));
	}

	return 0;
}
