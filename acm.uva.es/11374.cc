#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
using namespace std;
#define foreach(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

vector<int> adj[1024];
vector<long long> adjC[1024];
int N, src, dst, prev[2048];

long long dist[2048], INF = 1LL << 60;

struct Comparer {
	bool operator()(int i, int j) const {
		return (dist[i] != dist[j]) ? (dist[i] < dist[j]) : (i < j);
	}
};

void solve()
{
	for (int i = 0; i < 2*N; i++) {
		prev[i] = -1;
		dist[i] = INF;
	}

	prev[src] = src;
	dist[src] = 0;

	set<int, Comparer> Q;
	Q.insert(src);

	while (Q.size() != 0) {
		int u = *Q.begin();
		Q.erase(Q.begin());

		for (int i = 0; i < (int)adj[u].size(); i++) {
			int v = adj[u][i];
			long long c = adjC[u][i];
			if (dist[u] + c < dist[v]) {
				Q.erase(v);
				dist[v] = dist[u] + c;
				prev[v] = u;
				Q.insert(v);
			}
		}
	}

	int t = (dist[dst] <= dist[dst+N]) ? dst : (dst+N);
	assert(prev[t] != -1);

	int kappa = -1;

	vector<int> path;
	path.push_back(t);
	for (int x = t; x != src;) {
		if (x >= N && prev[x] < N)
			kappa = prev[x];
		x = prev[x];
		path.push_back(x);
	}

	for (int i = 0; i < (int)path.size(); i++) {
		printf(i == 0 ? "%d" : " %d", path[path.size()-1-i] % N + 1);
	}
	printf("\n");

	if (kappa == -1) {
		printf("Ticket Not Used\n");
	} else {
		printf("%d\n", kappa%N+1);
	}
	printf("%lld\n", dist[t] / 10000);
}

void add(int x, int y, long long z) {
	if (x == y) return;
	z = z * 10000 + 1;
	adj[x].push_back(y);
	adjC[x].push_back(z);
}

int main()
{
	int M1, M2, x, y, z;
	for (int cs = 1; scanf("%d %d %d", &N, &src, &dst) == 3 && N >= 1; cs++) {
		if (cs > 1) printf("\n");

		src--; dst--;
		for (int i = 0; i < 1024; i++) adj[i].clear();
		for (int i = 0; i < 1024; i++) adjC[i].clear();

		scanf("%d", &M1);
		for (int i = 0; i < M1; i++) {
			scanf("%d %d %d", &x, &y, &z);
			x--; y--;
			add(x, y, z);
			add(y, x, z);
			add(x+N, y+N, z);
			add(y+N, x+N, z);
		}

		scanf("%d", &M2);
		for (int i = 0; i < M2; i++) {
			scanf("%d %d %d", &x, &y, &z);
			x--; y--;
			add(x, y+N, z);
			add(y, x+N, z);
		}

		solve();
	}
}
