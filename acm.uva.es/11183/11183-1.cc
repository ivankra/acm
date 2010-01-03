#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

int ufind[1024];
int f(int x) {
	int z;
	for (z = ufind[x]; ufind[z] != z; z = ufind[z]);
	while (x != z) { int y = ufind[x]; ufind[x] = z; x = y; }
	return z;
}
void merge(int x, int y) { x = f(x); y = f(y); ufind[x] = y; }

struct Edge { int u, v, c; } E[50000];
int N, M, INF=1<<30;

int solve() {
	if (N <= 1) return 0;

	int par[1024];
	vector<int> in[1024];
	int answer = 0;

	for (int i = 0; i < N; i++) ufind[i] = i;
	for (int i = 0; i < N; i++) par[i] = -1;
	for (int i = 0; i < N; i++) in[i].clear();

	for (int i = 0; i < M; i++) {
		int x = f(E[i].u), y = f(E[i].v);
		if (x == y || y == f(0)) continue;

		if (par[y] < 0 || E[i].c < E[par[y]].c) par[y] = i;
		in[y].push_back(i);
	}

	int seen[1024], tick = 1;
	memset(seen, 0, sizeof(seen));

	for (;;) {
		bool done = true;

		for (int s = 0; s < N; s++) {
			if (f(s) != s || f(s) == f(0)) continue;

			tick++;
			seen[f(0)] = tick;

			int y = s;
			do {
				if (par[y] < 0) return INF;
				seen[y] = tick;
				y = f(E[par[y]].u);
			} while (seen[y] != tick);

			if (f(y) == f(0)) {
				for (int z = s; z != y;) {
					int p = f(E[par[z]].u);
					answer += E[par[z]].c;
					merge(z, p);
					z = p;
				}
				continue;
			}

			vector<int> v;
			for (int z = y;;) {
				int t = E[par[z]].c;
				answer += t;
				for (int i = 0; i < (int)in[z].size(); i++) {
					E[in[z][i]].c -= t;
					v.push_back(in[z][i]);
				}
				in[z].clear();
				int p = f(E[par[z]].u);
				par[z] = -1;
				merge(z, p);
				if (z == p) break;
				z = p;
			}
			y = f(y);
			in[y] = v;

			par[y] = -1;
			for (int i = 0; i < (int)in[y].size(); i++) {
				const Edge &e = E[in[y][i]];
				assert(f(e.v) == f(y));
				if (f(e.u) != f(y) && (par[y] < 0 || e.c < E[par[y]].c))
					par[y] = in[y][i];
			}
			if (par[y] < 0) return INF;

			done = false;
		}

		if (done) break;
	}

	return answer;
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d %d", &N, &M) == 2; cs++) {
		assert(0 <= N && N <= 1000);
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &E[i].u, &E[i].v, &E[i].c);
			assert(0 <= E[i].u && E[i].u < N);
			assert(0 <= E[i].v && E[i].v < N);
			assert(0 <= E[i].c && E[i].c <= 1000);
		}

		int res = solve();
		printf("Case #%d: ", cs);
		if (res >= INF)
			printf("Possums!\n");
		else
			printf("%d\n", res);
	}
}
