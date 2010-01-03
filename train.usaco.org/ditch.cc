/*
ID: infnty1
PROB: ditch
LANG: C++
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> VI;  typedef vector<VI> VVI;

struct Edge {
	int x, y, c, r;
};

vector<Edge> E;
VVI G;

int maxflow(int s, int t) {
	int flow = 0;
	for (;;) {
		VI prev(G.size(), -1), stk(1, s);

		prev[s] = 0;
		while (stk.size() > 0) {
			int x = stk.back(); stk.pop_back();
			for (int i = 0; i < (int)G[x].size(); i++) {
				int e = G[x][i];
				if (E[e].c > 0 && prev[E[e].y] < 0) {
					prev[E[e].y] = e;
					stk.push_back(E[e].y);
				}
			}
		}

		if (prev[t] < 0) return flow;

		int cap = 0x7fffffff;
		for (int x = t; x != s; x = E[prev[x]].x)
			cap <?= E[prev[x]].c;

		flow += cap;

		for (int x = t; x != s; x = E[prev[x]].x) {
			E[prev[x]].c -= cap;
			E[E[prev[x]].r].c += cap;
		}
	}
}

void add(int x, int y, int c) {
	Edge e1 = { x, y, c, E.size()+1 };
	Edge e2 = { y, x, 0, E.size() };
	G[x].push_back(E.size());
	G[y].push_back(E.size()+1);
	E.push_back(e1);
	E.push_back(e2);
}

int main()
{
	freopen("ditch.in", "r", stdin);
	freopen("ditch.out", "w", stdout);

	int n, m, x, y, z;
	scanf("%d %d", &m, &n);

	E.clear();
	G = VVI(n, VI());
	while (m-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3)
		add(x-1, y-1, z);

	printf("%d\n", maxflow(0, n-1));

	return 0;
}

