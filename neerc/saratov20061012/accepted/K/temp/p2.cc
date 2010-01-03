#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
typedef long long int64;

struct Edge {
	int x, y;
	bool operator ==(const Edge &e) const { return x==e.x && y==e.y; }
	Edge(int X, int Y) : x(X), y(Y) {
		if (x > y) swap(x, y);
	}
};

vector<int> adj[2048];   // second graph
vector<Edge> E1, E2;
vector<int> out;
int N;

int main() {
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	scanf("%d", &N);
	for (int i = 1; i <= N; i++) { adj1[i].clear(); adj2[i].clear(); }

	for (int z = 0; z < 2; z++) {
		for (int i = 0; i < N-1; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			if (x > y) swap(x, y);

			if (z == 0) {
				adj1[x].push_back(y);
				adj1[y].push_back(x);
				E1.push_back(Edge(x, y));
			} else {
				adj2[x].push_back(y);
				adj2[y].push_back(x);
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

		printf("Creating edge (%d, %d) in graph 2\n", E1[i].x, E1[i].y);

		adj2

		out.push_back(2);
		out.push_back(E1[i].x);
		out.push_back(E2[i].y);


	}


	return 0;
}