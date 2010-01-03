#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <cmath>
#include <cassert>
#include <map>
using namespace std;

#define MAXN 160
int N, G[MAXN][MAXN];

int StoerWagner()
{
	int best = 0x7FFFFFFF;
	int V[MAXN], A[MAXN], tightness[MAXN];
	for (int i = 0; i < N; i++) V[i] = i;    // V - list of vertices still in graph

	while (N > 1) {
		// initialize set A
		memset(A, 0, sizeof(A));
		A[V[0]] = 1;
		for (int i = 1; i < N; i++)
			tightness[V[i]] = G[V[0]][V[i]];

		int s, t;

		for (int k = 1; ; k++) {
			// find most tightly-connected vertex
			int x = -1, xtight = -1;
			for (int i = 0; i < N; i++) {
				if (!A[V[i]] && tightness[V[i]] > xtight) {
					x = V[i];
					xtight = tightness[V[i]];
				}
			}

			// store last two added vertices
			if (k == N-2) s = x;
			if (k == N-1) { t = x; best = min(best, xtight); break; }

			// add it to set A
			A[x] = 1;
			for (int i = 0; i < N; i++)
				if (!A[V[i]]) tightness[V[i]] += G[x][V[i]];
		}

		// contract s and t
		for (int i = 0; i < N; i++)
			if (V[i] == t) { swap(V[i], V[N-1]); break; }
		for (int i = 0; i < N-1; i++) {
			G[s][V[i]] += G[t][V[i]];
			G[V[i]][s] += G[V[i]][t];
		}
		G[s][t] = 0;
		N--;
	}

	return best;
}

int main()
{
	int T, M;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &N, &M);
		memset(G, 0, sizeof(G));
		for (int i = 0; i < M; i++) {
			int u, v, c;
			scanf("%d %d %d", &u, &v, &c);
			u--; v--;
			G[u][v] += c;
			G[v][u] += c;
		}
		printf("Case #%d: %d\n", cs, StoerWagner());
	}
}
