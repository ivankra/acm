/*
 *  Implementation of a min-cost max-flow solver,
 *  using Bellman-Ford algorithm at each iteration.
 */
#include <algorithm>
#include <vector>
using namespace std;

struct MCMF {
	typedef int ctype;
	enum { MAXN = 1000, INF = INT_MAX };
	struct Edge { int x, y; ctype cap, cost; };
	vector<Edge> E;
	vector<int> adj[MAXN];
	int N, prev[MAXN];
	ctype dist[MAXN];

	MCMF(int NN) : N(NN) {}

	void add(int x, int y, ctype cap, ctype cost) {
		Edge e1={x,y,cap,cost}, e2={y,x,0,-cost};
		adj[e1.x].push_back(E.size()); E.push_back(e1);
		adj[e2.x].push_back(E.size()); E.push_back(e2);
	}

	void mcmf(int s, int t, ctype &flowVal, ctype &flowCost) {
		int x;
		flowVal = flowCost = 0;
		while (true) {
			for (x = 0; x < N; x++) prev[x] = -1;
			for (x = 0; x < N; x++) dist[x] = INF;
			dist[s] = prev[s] = 0;

			for (x = 1; x;) {
				x = 0;
				Edge *begin = &E[0], *end = &E[E.size()];
				for (Edge *e = begin; e < end; ++e) {
					if (e->cap > 0 && prev[e->x] != -1 && dist[e->x] + e->cost < dist[e->y]) {
						dist[e->y] = dist[e->x] + e->cost;
						prev[e->y] = e - begin;
						x = 1;
					}
				}
			}
			if (prev[t] == -1) break;

			ctype z = INF;
			for (x = t; x != s; x = E[prev[x]].x)
				z = min(z, E[prev[x]].cap);
			for (x = t; x != s; x = E[prev[x]].x)
				{ E[prev[x]].cap -= z; E[prev[x]^1].cap += z; }
			flowVal += z; flowCost += z * dist[t];
		}
	}
};

