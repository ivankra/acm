#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

struct edge {
	int x, y, c, c0, r, s;
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

void add(int x, int y, int c, int s) {
	struct edge e;
	e.x = x; e.y = y; e.c = e.c0 = c; e.s = s;
	e.r = E.size()+1;
	G[x].push_back(E.size());
	E.push_back(e);
	swap(e.x, e.y);
	e.r = E.size()-1;
	e.c = e.c0 = 0;
	G[y].push_back(E.size());
	E.push_back(e);
}

int main()
{
	int T, cs = 1, n, m, d, ex, ey, ec, es, ed;
	for (scanf("%d", &T); cs <= T && scanf("%d %d %d", &n, &d, &m) == 3; cs++) {
		assert(1 <= n && n <= 30 && 1 <= d && d <= 10);

		d++;
		G = VVI(1+n*d, VI());
		E.clear();
		VI costs(1, 0);
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d %d %d", &ex, &ey, &ec, &es, &ed);
			assert(1 <= ex && ex <= n && 1 <= ey && ey <= n && 0 <= ed && ed <= d-2);
			add(1+(ex-1)+ed*n, 1+(ey-1)+(ed+1)*n, ec, es);
			costs.push_back(es);
		}
	
		sort(costs.begin(), costs.end());
		costs.erase(unique(costs.begin(), costs.end()), costs.end());

		ey = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < d-1; j++)
				add(1+i+j*n, 1+i+(j+1)*n, 1000000, 0);
			scanf("%d", &ex);
			ey += ex;
			add(0, 1+i, ex, 0);
		}

		int a, b;
		for (a = 0, b = costs.size()-1; a <= b;) {
			int c = (a + b) / 2, k = costs[c];

			for (int i = 0; i < (int)E.size(); i++)
				E[i].c = (E[i].s <= k) ? E[i].c0 : 0;

			if (flow(0, 1+(n-1)+(d-1)*n) >= ey) {
				b = c;
				if (a == b) break;
			} else {
				a = c + 1;
			}
		}

		printf("Case #%d: ", cs);
		if (a > b)
			printf("Impossible\n");
		else
			printf("%d\n", costs[a]);
	}
	return 0;
}
