/*
ID: infnty1
PROB: milk6
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> VI;  typedef vector<VI> VVI;

struct Edge {
	int u, v, rev;
	long long c, r;
	Edge(int U=0, int V=0, long long C=0, int Rev=0) : u(U), v(V), rev(Rev), c(C), r(0) {}
};

Edge E[2048];
VVI adj;
int N, seen[50];

int dfs(int x, int y) {
	if (x == y) return 1;
	if (seen[x]++) return 0;
	for (int i = 0; i < (int)adj[x].size(); i++) {
		Edge &e = E[adj[x][i]];
		if (e.r > 0 && dfs(e.v, y)) return 1;
	}
	return 0;
}

long long aug(int s, int t, long long lim) {
	if (s == t || lim <= 0) return 0;

	static int q[100], p[100];
	for (int i = 0; i < N; i++) p[i] = -1;

	int *qh = q, *qt = q;
	*qt++ = s;
	p[s] = -2;
	while (qh < qt && p[t] < 0) {
		int x = *qh++;
		for (int i = 0; i < (int)adj[x].size(); i++) {
			int e = adj[x][i];
			if (E[e].r > 0 && p[E[e].v] == -1)
				p[*qt++ = E[e].v] = e;
		}
	}
	if (p[t] < 0) return 0;

	long long c = lim;
	for (int x = t; x != s; x = E[p[x]].u)
		c <?= E[p[x]].r;

	for (int x = t; x != s; x = E[p[x]].u) {
		E[p[x]].r -= c;
		E[E[p[x]].rev].r += c;
	}

	return c;
}

long long flow(int s, int t, long long lim = 1LL<<60) {
	long long f = 0, a;
	while (f < lim && (a = aug(s, t, lim-f)) > 0)
		f += a;
	return f;
}

int main() {
	freopen("milk6.in", "r", stdin);
	freopen("milk6.out", "w", stdout);

	int M;
	scanf("%d %d", &N, &M);
	adj.assign(N, VI());
	for (int i = 0; i < M; i++) {
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		u--; v--;
		E[i] = Edge(u, v, c*(M+1)+1, M+i);
		E[M+i] = Edge(v, u, 0, i);
		adj[u].push_back(i);
		adj[v].push_back(M+i);
	}

	for (int i = 0; i < 2*M; i++) E[i].r = E[i].c;

	long long f = flow(0, N-1);
	printf("%lld %lld\n", f/(M+1), f%(M+1));

	for (int i = 0; i < M; i++) {
		Edge &e = E[i], &e1 = E[E[i].rev];
		if (e.r != 0 || e.c <= 0) continue;

		assert(e1.r == e.c);

		e1.r = 0;
		memset(seen, 0, sizeof(seen));
		if (dfs(e.u, e.v)) {
			e1.r = e.c;
			continue;
		}

		printf("%d\n", i+1);

		e.r = e1.r = 0;

		flow(e.u, 0, e.c);
		flow(N-1, e.v, e.c);

		e.c = e1.c = 0;
	}

	return 0;
}
