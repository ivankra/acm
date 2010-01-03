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
#include <map>
using namespace std;
#define foreach(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

int N, vcost[2100];
vector<int> adj[2100];

int solve(int s, int t)
{
	static int dist[2100];
	vector<int> qcur, qnext;

	if (s == t)
		return 0;

	for (int i = 0; i <= N; i++)
		dist[i] = 0x3fffffff;

	qcur.push_back(s);
	dist[s] = vcost[s];

	while (true) {
		if (qcur.size() == 0) {
			qcur.swap(qnext);
			if (qcur.size() == 0) return -1;
		}

		int x = qcur.back();
		qcur.pop_back();

		if (x == t)
			return dist[t];

		for (int i = 0; i < (int)adj[x].size(); i++) {
			int y = adj[x][i];
			if (dist[x] + vcost[y] < dist[y]) {
				dist[y] = dist[x] + vcost[y];
				if (vcost[y] == 0)
					qcur.push_back(y);
				else
					qnext.push_back(y);
			}
		}
	}
}

int main()
{
	int T, M, K, x, y;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d", &N, &M, &K);
		memset(vcost, 0, sizeof(vcost));

		for (int i = 0; i <= N; i++) {
			vcost[i] = 1;
			adj[i].clear();
		}

		for (int i = 0; i < K; i++) {
			scanf("%d", &x);
			vcost[x] = 0;
		}

		for (int i = 0; i < M; i++) {
			scanf("%d %d", &x, &y);
			adj[x].push_back(y);
			adj[y].push_back(x);
		}

		int Q, s, t;
		scanf("%d", &Q);
		printf("Case %d:\n", cs);
		for (int q = 1; q <= Q; q++) {
			scanf("%d %d", &s, &t);
			printf("%d\n", solve(s, t));
		}
		printf("\n");
	}
}
