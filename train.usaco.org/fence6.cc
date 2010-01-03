/*
ID: infnty1
PROB: fence6
LANG: C++
*/
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef vector<int> VI;
#define INF 0x3fffffff

struct Fence {
        int len;
        VI adj[2];
} F[128];

int main()
{
        freopen("fence6.in", "r", stdin);
        freopen("fence6.out", "w", stdout);

	int N;
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
                int s, n[2], x; scanf("%d", &s); s--;
                scanf("%d %d %d", &F[s].len, &n[0], &n[1]);
                for (int k = 0; k < 2; k++) {
                        F[s].adj[k] = VI();
                        for (int j = 0; j < n[k] && scanf("%d", &x) == 1; j++)
                                F[s].adj[k].push_back(x-1);
                }
        }

        int best = INF;
	for (int st = 0; st < N; st++) {
		int d[128], seen[128], init[128], u, v;
		for (int i = 0; i < N; i++) { d[i] = INF; seen[i] = init[i] = 0; }

		for (int i = 0; i < (int)F[st].adj[0].size(); i++) {
			v = F[st].adj[0][i];
			d[v] = F[st].len + F[v].len;
			init[v] = 1;
		}
		seen[st] = 1;

		for (;;) {
			u = -1;
			for (v = 0; v < N; v++)
				if (!seen[v] && (u < 0 || d[v] < d[u])) u = v;
			if (u < 0 || d[u] >= INF) break;

			seen[u] = 1;

			for (int k = 0; k < 2; k++)
			for (int i = 0; i < (int)F[u].adj[k].size(); i++) {
				v = F[u].adj[k][i];
				if (v == st && !init[u]) best <?= d[u] + F[u].len + F[v].len;
				if (!seen[v]) d[v] <?= d[u] + F[u].len + F[v].len;
			}
		}

	}

        printf("%d\n", best/2);
        return 0;
}
