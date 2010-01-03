#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
using namespace std;
#define SIZE(x) int((x).size())
#define FOREACH(it, x) for(__typeof((x).begin())it=(x).begin();it!=(x).end();++it)
typedef long long LL;
typedef vector<int> VI;

struct Edge {
	int y, len, tm;
};

int N, velocity, src, dst, deg[20000], prev[20000];
Edge *adj[20000];
long long dist[20000];

struct Cmp {
	bool operator()(int i, int j) {
		if (i == j) return false;
		return dist[i] == dist[j] ? (i < j) : (dist[i] < dist[j]);
	}
};

int main()
{
	scanf("%d %d %d %d", &N, &velocity, &src, &dst);

	for (int i = 1; i <= N; i++) {
		scanf("%d", &deg[i]);
		adj[i] = new Edge[deg[i]];
		for (int j = 0; j < deg[i]; j++)
			scanf("%d %d %d", &adj[i][j].y, &adj[i][j].len, &adj[i][j].tm);
	}

	for (int i = 1; i <= N; i++) dist[i] = LLONG_MAX;
	dist[src] = 0;
	memset(prev, 0xff, sizeof(prev));
	prev[src] = src;

	set<int, Cmp> Q;
	Q.insert(src);

	while (!Q.empty()) {
		int x = *Q.begin();
		Q.erase(Q.begin());

		for (int i = 0; i < deg[x]; i++) {
			Edge *e = &adj[x][i];

			LL dd = dist[x] + e->len;
			if (dd > e->tm * (LL)velocity) continue;

			if (dd < dist[e->y]) {
				Q.erase(e->y);
				dist[e->y] = dd;
				prev[e->y] = x;
				Q.insert(e->y);
			}
		}
	}

	if (prev[dst] < 0) {
		printf("0\n");
	} else {
		VI path;
		for (int x = dst; x != src; x = prev[x])
			path.push_back(x);
		path.push_back(src);
		reverse(path.begin(), path.end());

		printf("%d\n", SIZE(path));
		for (int i = 0; i < SIZE(path); i++)
			printf(i == 0 ? "%d" : " %d", path[i]);
		printf("\n");
	}
}
