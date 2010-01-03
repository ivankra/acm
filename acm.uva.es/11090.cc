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

struct Edge { int u, v, w; } e[10000];
int N, M;
long long d[64][64], INF=1LL<<62;

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d %d", &N, &M) == 2; cs++) {
		for (int i = 0; i < M; i++)
			scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);

		for (int i = 1; i <= N; i++) d[0][i] = 0;
		for (int k = 1; k <= N; k++) {
			for (int i = 1; i <= N; i++) d[k][i] = INF;
			for (int i = 0; i < M; i++) d[k][e[i].v] <?= d[k-1][e[i].u] + e[i].w;
		}

		bool flag = false;
		for (int i = 1; i <= N; i++)
			flag |= (d[N][i] < INF);

		printf("Case #%d: ", cs);
		if (flag) {
			double res = 1e99;
			for (int i = 1; i <= N; i++) {
				if (d[N][i] == INF) continue;
				double t = 0;
				for (int k = 0; k < N; k++) {
					if (d[k][i] == INF) continue;
					t >?= (d[N][i] - d[k][i]) / double(N - k);
				}
				res <?= t;
			}
			printf("%.2f\n", res);
		} else {
			printf("No cycle found.\n");
		}
	}
}
