#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
using namespace std;

int N;

struct Edge {
	int x, y;
	Edge(int X, int Y) : x(X), y(Y) {}
};

struct Graph {
	char adj[2048][2048];
	vector<int> lst[2048];
	vector<Edge> E;
	int cyc[2048], seen[2048];

	void clear() {
		memset(adj, 0, sizeof(adj));
		for (int i = 1; i <= N; i++) lst[i].clear();
		E.clear();
	}

	void add(int x, int y) {
		if (x > y) swap(x, y);
		assert(1 <= x && x < y && y <= N);
		assert(adj[x][y] == 0);
		adj[x][y] = adj[y][x] = 1;
		lst[x].push_back(y);
		lst[y].push_back(x);
		E.push_back(Edge(x, y));
	}

	void remove(int x, int y) {
		if (x > y) swap(x, y);
		assert(1 <= x && x < y && y <= N);
		assert(adj[x][y] == 1);
		adj[x][y] = adj[y][x] = 0;
		for (int i = 0; i < (int)lst[x].size(); i++)
			if (lst[x][i] == y) { lst[x].erase(lst[x].begin()+i); break; }
		for (int i = 0; i < (int)lst[y].size(); i++)
			if (lst[y][i] == x) { lst[y].erase(lst[y].begin()+i); break; }
		for (int i = 0; i < (int)E.size(); i++)
			if (E[i].x == x && E[i].y == y) { E.erase(E.begin()+i); break; }
	}

	int dfs(int x, int p) {
		if (seen[x]) return 1;
		seen[x] = 1;

		for (int i = 0; i < (int)lst[x].size(); i++) {
			int y = lst[x][i];
			if (y == p) continue;
			if (dfs(y, x)) { cyc[x] = 1; return 1; }
		}

		return 0;
	}

	void find_cycle(int s) {
		memset(cyc, 0, sizeof(cyc));
		memset(seen, 0, sizeof(seen));
		dfs(s, 0);
	}
} G[2];

int main()
{
	cin >> N;

	G[0].clear();
	G[1].clear();

	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < N-1; i++) {
			int x, y;
			cin >> x >> y;
			G[k].add(x, y);
		}
	}

	vector<string> out;
	for (int x = 1; x <= N; x++) {
		for (int y = x+1; y <= N; y++) {
			if (G[0].adj[x][y] == G[1].adj[x][y]) continue;
			if (G[0].adj[x][y] == 1) continue;

			G[0].add(x, y);
			G[0].find_cycle(x);

			int x1 = 0, y1 = 0;
			for (int i = 0; i < (int)G[0].E.size(); i++) {
				Edge &e = G[0].E[i];
				if (G[0].cyc[e.x] && G[0].cyc[e.y] && G[1].adj[e.x][e.y] == 0) {
					x1 = e.x;
					y1 = e.y;
					break;
				}
			}
			assert(x1 > 0 && y1 > 0);

			G[0].remove(x1, y1);

			ostringstream os;
			os << "1 " << x << " " << y << " " << x1 << " " << y1;
			out.push_back(os.str());
		}
	}

	cout << out.size() << endl;
	for (int i = 0; i < (int)out.size(); i++)
		cout << out[i] << endl;
}
