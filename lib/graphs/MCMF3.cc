/*
 *  Implementation of a min-cost max-flow solver,
 *  using Dijkstra algorithm at each iteration, STL version.
 */
#include <algorithm>
#include <vector>
#include <set>
#include <cstring>
#include <cassert>
#include <climits>
using namespace std;
#define FOREACH(it,x) for(__typeof((x).begin())it=(x).begin();it!=(x).end();++it)

struct MCMF {
	typedef long long ctype;
	enum { MAXN = 1000, INF = LLONG_MAX };
	struct Edge { int x, y; ctype cap, cost; };
	vector<Edge> E;
	vector<int> adj[MAXN];
	int N, prev[MAXN];
	ctype dist[MAXN], phi[MAXN];

	MCMF(int NN) : N(NN) {}

	void add(int x, int y, ctype cap, ctype cost) {  // cost>=0
		Edge e1={x,y,cap,cost}, e2={y,x,0,-cost};
		adj[e1.x].push_back(E.size()); E.push_back(e1);
		adj[e2.x].push_back(E.size()); E.push_back(e2);
	}

	struct Cmp {
		ctype *dist;
		Cmp(ctype *d) { dist = d; }
		bool operator()(int i, int j) const {
			return (dist[i] != dist[j]) ? (dist[i] < dist[j]) : (i < j);
		}
	};

	void mcmf(int s, int t, ctype &flowVal, ctype &flowCost) {
		int x;
		flowVal = flowCost = 0;
		memset(phi, 0, sizeof(phi));

		while (true) {
			for (x = 0; x < N; x++) prev[x] = -1;
			for (x = 0; x < N; x++) dist[x] = INF;
			dist[s] = prev[s] = 0;

			Cmp cmp = Cmp(this->dist);
			set<int, Cmp> Q(cmp);
			Q.insert(s);
			while (!Q.empty()) {
				x = *Q.begin(); Q.erase(Q.begin());
				FOREACH(it, adj[x]) {
					const Edge &e = E[*it];
					if (e.cap <= 0) continue;
					ctype cc = e.cost + phi[x] - phi[e.y];
					assert(cc >= 0);
					if (dist[x] + cc < dist[e.y]) {
						Q.erase(e.y);
						dist[e.y] = dist[x] + cc;
						prev[e.y] = *it;
						Q.insert(e.y);
					}
				}
			}
			if (prev[t] == -1) break;

			ctype z = INF;
			for (x = t; x != s; x = E[prev[x]].x)
				z = min(z, E[prev[x]].cap);
			for (x = t; x != s; x = E[prev[x]].x)
				{ E[prev[x]].cap -= z; E[prev[x]^1].cap += z; }
			flowVal += z;
			flowCost += z * (dist[t] + phi[t] - phi[s]);

			for (x = 0; x < N; x++)
				if (prev[x] != -1) phi[x] += dist[x];
		}
	}
};
