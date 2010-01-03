/*
 *  Implementation of a min-cost max-flow solver,
 *  using Dijkstra algorithm at each iteration and hand-made heap.
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
	enum { MAXN = 110, INF = LLONG_MAX };
	struct Edge { int x, y; ctype cap, cost; };
	vector<Edge> E;
	vector<int> adj[MAXN];
	int N, prev[MAXN], heap[MAXN], heapPos[MAXN], heapN;
	ctype dist[MAXN], phi[MAXN];

	MCMF(int NN) : N(NN) {}

	void add(int x, int y, ctype cap, ctype cost) {  // cost>=0
		Edge e1={x,y,cap,cost}, e2={y,x,0,-cost};
		adj[e1.x].push_back(E.size()); E.push_back(e1);
		adj[e2.x].push_back(E.size()); E.push_back(e2);
	}

	void heapSwap(int i, int j) {
		int t = heap[i];
		heap[i] = heap[j];
		heap[j] = t;
		heapPos[heap[i]] = i;
		heapPos[heap[j]] = j;
	}

	void heapUp(int i) {
		while (i > 0 && dist[heap[i]] < dist[heap[(i-1)/2]]) {
			int j = (i - 1) / 2;
			heapSwap(i, j);
			i = j;
		}
	}

	void heapDown(int i) {
		int j;
		while (2*i+1 < heapN) {
			j = 2 * i + 1;
			if (j + 1 < heapN && dist[heap[j+1]] < dist[heap[j]]) j++;
			if (dist[heap[i]] <= dist[heap[j]]) break;
			heapSwap(i, j);
			i = j;
		}
	}

	void mcmf(int s, int t, ctype &flowVal, ctype &flowCost) {
		int x;
		flowVal = flowCost = 0;
		memset(phi, 0, sizeof(phi));

		while (true) {
			for (x = 0; x < N; x++) prev[x] = -1;
			for (x = 0; x < N; x++) dist[x] = INF;
			dist[s] = prev[s] = 0;

			memset(heapPos, 0xff, sizeof(heapPos));
			heapPos[heap[0] = s] = 0;
			heapN = 1;

			while (heapN > 0) {
				x = heap[0];
				if (--heapN > 0) {
					heapPos[heap[0] = heap[heapN]] = 0;
					heapDown(0);
				}

				FOREACH(it, adj[x]) {
					const Edge &e = E[*it];
					if (e.cap <= 0) continue;
					ctype cc = e.cost + phi[x] - phi[e.y];
					assert(cc >= 0);
					if (dist[x] + cc < dist[e.y]) {
						dist[e.y] = dist[x] + cc;
						prev[e.y] = *it;
						if (heapPos[e.y] == -1) {
							heapPos[heap[heapN] = e.y] = heapN;
							heapN++;
						}
						heapUp(heapPos[e.y]);
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
