/*
 *  Implementation of Edmonds-Karp algorithm.
 *
 *  Graph::Graph(int n)
 *  Creates an empty graph with n vertices labelled 0, 1, ..., n-1.
 *
 *  void Graph::add(int x, int y, int c, bool undirected = false);
 *  Adds an edge from x to y of capacity c.
 *  If undirected = true, also add identical edge from y to x.
 *
 *  int Graph::maxflow(int s, int t);
 *  Computes maximum flow between vertices s and t, and returns its value.
 *  The network's state is dirtied by this operation.
 */
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct Graph {
	struct Edge { int x, y, c, r; };

	vector<Edge> E;
	vector<vector<int> > A;

	Graph(int n) { A.resize(n+1); }

	void add(int x, int y, int c, bool undirected = false) {
		Edge e1 = { x, y, c, E.size()+1 };
		A[x].push_back(E.size()); E.push_back(e1);
		Edge e2 = { y, x, undirected ? c : 0, E.size()-1 };
		A[y].push_back(E.size()); E.push_back(e2);
	}

	int maxflow(int s, int t) {
		vector<int> p(A.size(), -1), q(A.size()+1);
		int flow = 0;
		while (true) {
			fill(p.begin(), p.end(), -1);
			p[s] = s;

			q[0] = s;
			for (int qh = 0, qt = 1; qh < qt && p[t] < 0; qh++) {
				int x = q[qh];
				vector<int>::iterator e = A[x].begin();
				for (; e != A[x].end(); ++e) {
					int y = E[*e].y;
					if (p[y] < 0 && E[*e].c != 0)
						p[q[qt++] = y] = *e;
				}
			}
			if (p[t] < 0) break;

			int c = 0x7fffffff;
			for (int x = t; x != s; x = E[p[x]].x)
				c = min(c, E[p[x]].c);

			for (int x = t; x != s; x = E[p[x]].x) {
				E[p[x]].c -= c;
				E[E[p[x]].r].c += c;
			}
			flow += c;
		}
		return flow;
	}
};

int main() {
	Graph G(10);

	G.add(0, 1,  10);
	G.add(1, 2,  5);
	G.add(1, 3,  7);
	G.add(2, 4,  8);
	G.add(3, 4,  8);

	int f = G.maxflow(0, 4);
	printf("f = %d  (must be 10)\n", f);

	return 0;
}
