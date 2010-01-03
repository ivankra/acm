/*
ID: infnty1
PROB: butter
LANG: C++
*/
#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
typedef vector<int> VI; typedef vector<VI> VVI;

#define INF 0x3fffffff

int N, M, ncows;
VVI adj, cost;
VI cows, dist;

struct Thing {
	int x, d;
	Thing(int X, int D) : x(X), d(D) {}
	bool operator <(const Thing &a) const { return d > a.d; }
};

int solve(int s) {
	dist.assign(N, INF);
	dist[s] = 0;

	priority_queue<Thing> pq;
	pq.push(Thing(s, 0));

	while (!pq.empty()) {
		int x = pq.top().x; pq.pop();
		for (int i = 0; i < (int)adj[x].size(); i++) {
			int y = adj[x][i];
			if (dist[y] > dist[x] + cost[x][i]) {
				dist[y] = dist[x] + cost[x][i];
				pq.push(Thing(y, dist[y]));
			}
		}
	}

	int res = 0;
	for (int i = 0; i < N; i++)
		res += cows[i] * dist[i];
	return res;
}

void edge(int x, int y, int c) {
	if (x != y) {
		adj[x].push_back(y); cost[x].push_back(c);
		adj[y].push_back(x); cost[y].push_back(c);
	}
}

int main() {
	freopen("butter.in", "r", stdin);
	freopen("butter.out", "w", stdout);

	scanf("%d %d %d", &ncows, &N, &M);
	adj.assign(N, VI());
	cost.assign(N, VI());
	cows.assign(N, 0);

	int x, y, c;
	for (int i = 0; i < ncows; i++) {
		scanf("%d", &x);
		cows[x-1]++;
	}

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &x, &y, &c);
		edge(x-1, y-1, c);
	}

	int best = INF;
	for (x = 0; x < N; x++)
		best = min(best, solve(x));
	printf("%d\n", best);
}
