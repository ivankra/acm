#include <cstdio>
#include <vector>
#include <algorithm>
#define EPS 1e-11
using namespace std;
typedef vector<int> VI; typedef vector<VI> VVI;

struct edge {
	int x, y, cap, r;
	double cost;
	edge(int x, int y, int c, double s, int r) : x(x), y(y), cap(c), r(r), cost(s) {}
};

vector<edge> E;
VVI G;

void mkedge(int x, int y, int c, double s) {
	int e1 = E.size(), e2 = E.size()+1;
	E.push_back(edge(x, y, c, s, e2));
	E.push_back(edge(y, x, 0, -s, e1));
	G[x].push_back(e1);
	G[y].push_back(e2);
}

double aug() {
	vector<double> dist(G.size(), 1e99);
	VI pred(G.size(), -1), path;

	dist[0] = 0;

	for (int i = 0, f = 0; i < (int)G.size(); i++) {
		for (int j = 0; j < (int)E.size(); j++) {
			if (E[j].cap == 0) continue;
			if (dist[E[j].y] < dist[E[j].x] + E[j].cost + EPS)
				continue;
			dist[E[j].y] = dist[E[j].x] + E[j].cost;
			pred[E[j].y] = j;
			f++;
		}
		if (f == 0) break;
	}

	if (pred[1] < 0) return 0.;

	int c = E[pred[1]].cap;
	for (int x = 1; x > 0; x = E[pred[x]].x)
		c <?= E[pred[x]].cap;

	for (int x = 1; x > 0; x = E[pred[x]].x) {
		int e = pred[x];
		E[e].cap -= c;
		E[E[e].r].cap += c;
	}

	return c * dist[1];
}

int main()
{
	double c;
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		G = VVI(2+n+m, VI());
		E.clear();
		for (int i = 0; i < n; i++) {
			mkedge(0, 2+i, 1, 0);
			for (int j = 0; j < m && scanf("%lf", &c) == 1; j++)
				mkedge(2+i, 2+n+j, 1, c);
		}

		for (int i = 0; i < m; i++)
			mkedge(2+n+i, 1, 1, 0);

		c = 0;
		for (int i = 0; i < n; i++)
			c += aug();

		printf("%.2f\n", c/n+EPS);
	}
	return 0;
}
