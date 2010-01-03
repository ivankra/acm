#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

struct Edge {
	int x, y;

	bool operator ==(const Edge &e) const { return x==e.x && y==e.y; }
	Edge(int X, int Y) : x(X), y(Y) {
		if (x > y) swap(x, y);
	}
};

vector<Edge> E1, E2, cycle;
vector<int> adj[2048], out;
char G1[2048][2048];
int seen[2048], N;

bool dfs(int x, int parent) {
	if (seen[x]) return true;
	seen[x] = 1;

	for (int i = 0; i < (int)adj[x].size(); i++) {
		int y = adj[x][i];
		if (y == parent) continue;

		if (dfs(y, x)) {
			cycle.push_back(Edge(x, y));
			return true;
		}
	}

	return false;
}

int main() {
	freopen("input.txt", "r", stdin);
#ifndef STAVSU_DEBUG
	freopen("output.txt", "w", stdout);
#endif

	scanf("%d", &N);
	for (int i = 1; i <= N; i++) adj[i].clear();

	memset(G1, 0, sizeof(G1));
	for (int z = 0; z < 2; z++) {
		for (int i = 0; i < N-1; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			if (x > y) swap(x, y);

			if (z == 0) {
				E1.push_back(Edge(x, y));
				G1[x][y] = G1[y][x] = 1;
			} else {
				E2.push_back(Edge(x, y));
			}
		}
	}

	out.clear();

	for (int i = 0; i < N-1; i++) {
		bool common = false;
		for (int j = 0; j < N-1; j++)
			if (E2[j] == E1[i]) { common = true; break; }
		if (common) continue;

#ifdef STAVSU_DEBUG
		printf("Creating edge (%d, %d) in graph 2\n", E1[i].x, E1[i].y);
#endif

		E2.push_back(E1[i]);

		for (int i = 1; i <= N; i++) adj[i].clear();
		for (int i = 0; i < (int)E2.size(); i++) {
			adj[E2[i].x].push_back(E2[i].y);
			adj[E2[i].y].push_back(E2[i].x);
		}

		cycle.clear();
		memset(seen, 0, sizeof(seen));
		dfs(E1[i].x, -1);

#ifdef STAVSU_DEBUG
		printf("Found cycle: ");
		for (int i = 0; i < (int)cycle.size(); i++) {
			Edge &e = cycle[i];
			printf("(%d,%d) ", e.x, e.y);
		}
		printf("\n");
#endif
		out.push_back(2);
		out.push_back(E1[i].x);
		out.push_back(E1[i].y);

		Edge what(1,2);

		for (int i = 0; i < (int)cycle.size(); i++) {
			Edge &e = cycle[i];
			if (!G1[e.x][e.y]) {
				what = e;
			}
		}
#ifdef STAVSU_DEBUG
		printf("Removing edge (%d,%d) from the 2nd graph\n", what.x, what.y);
#endif

		for (int i = 0; i < (int)E2.size(); i++) {
			if (E2[i] == what) {
				E2.erase(E2.begin()+i);
				break;
			}
		}

		out.push_back(what.x);
		out.push_back(what.y);
	}

	printf("%d\n", out.size()/5);
	for (int i = 0; i < (int)out.size(); i += 5)
		for (int j = 0; j < 5; j++)
			printf(j<4 ? "%d " : "%d\n", out[i+j]);
	fflush(stdout);

	return 0;
}