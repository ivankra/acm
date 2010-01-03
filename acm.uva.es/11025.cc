#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

#define INF 0x3fffffff

int N, M, carSpeed, adj[16][16], dist[16][16], deg[16];
long long memo[13][1<<13];
int best[13][1<<13];

long long f(int at, int sub) {
	sub &= ~(1 << at);

	long long &res = memo[at][sub];
	if (res >= 0) return res;

	if (sub == 0)
		return res = deg[at] * (long long)dist[at][0];

	int sum = 0;
	for (int u = 0; u < N; u++)
		if (sub & (1 << u)) sum += deg[u];

	res = 1LL<<60;
	for (int u = 0; u < N; u++) {
		if ((sub & (1 << u)) == 0) continue;

		long long t = deg[at] * (long long)dist[at][0] + sum * (long long)dist[at][u] + f(u, sub);
		if (t < res) {
			res = t;
			best[at][sub] = u;
		}
	}

	return res;
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d %d %d", &N, &M, &carSpeed) == 3; cs++) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				adj[i][j] = INF;

		for (int i = 0; i < M; i++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			adj[u][v] = adj[v][u] = w;
		}

		for (int i = 0; i < N; i++) {
			deg[i] = 0;
			for (int j = 0; j < N; j++)
				if (adj[i][j] < INF) deg[i]++;
		}

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				dist[i][j] = (i == j ? 0 : adj[i][j]);

		for (int k = 0; k < N; k++)
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					dist[i][j] <?= dist[i][k] + dist[k][j];

		memset(memo, 0xff, sizeof(memo));
		long long num = f(0, (1<<N)-1);
		long long den = 2*M*carSpeed;

		long long g = __gcd(num, den);
		num /= g; den /= g;

		printf("Case %d:\n%lld/%lld\n", cs, num, den);
		printf("0");
		for (int at = 0, s = ((1<<N)-1)^(1<<at); s != 0;) {
			printf(" %d", best[at][s]);
			at = best[at][s];
			if (at < 0) break;
			s &= ~(1 << at);
		}
		printf("\n");
		if (cs < T) printf("\n");
	}
}
