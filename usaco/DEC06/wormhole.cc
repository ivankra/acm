/*
ID: infnty1
LANG: C++
TASK: wormhole
*/
#define TASK "wormhole"
#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

struct Edge {
	int x, y;
	long long c;
};

int N;
vector<Edge> E;

bool negcycle()
{
	long long dist[512];
	for (int i = 1; i <= N; i++) dist[i] = 0;

	for (int i = 0;; i++) {
		bool flag = false;
		for (int j = 0; j < (int)E.size(); j++) {
			const Edge &e = E[j];
			if (dist[e.x] + e.c < dist[e.y]) {
				flag = true;
				dist[e.y] = dist[e.x] + e.c;
			}
		}
		if (!flag) return false;
		if (i >= N) return true;
	}
}

int main()
{
	freopen(TASK ".in", "r", stdin);
	freopen(TASK ".out", "w", stdout);

	int F;
	scanf("%d", &F);

	for (int cs = 1; cs <= F; cs++) {
		int M, W;
		scanf("%d %d %d", &N, &M, &W);

		E.clear();
		for (int i = 0; i < M+W; i++) {
			Edge e;
			scanf("%d %d %lld", &e.x, &e.y, &e.c);
			if (i < M) {
				E.push_back(e);
				swap(e.x, e.y);
				E.push_back(e);
			} else {
				e.c = -e.c;
				E.push_back(e);
			}
		}

		printf(negcycle() ? "YES\n" : "NO\n");
	}
}
