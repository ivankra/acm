#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;i++)

int N, parent[200], kid[200], sib[200], memo[200][200], INF=1<<25;
vector<int> adj[200];

int g(int x, int k);

int f(int x, int k) {
	int &res = memo[x][k];
	if (res != -1) return res;

	if (x == 0) return res = (k==0 ? 0 : INF);

	assert(2 <= x && x <= N && k >= 0);

	res = 1 + f(sib[x], k);

	for (int u = 1; u <= k; u++)
		res <?= g(x, u) + f(sib[x], k-u);
	return res;
}

int g(int x, int k) {
	assert(1 <= x && x <= N && k >= 0);
	int deg = adj[x].size() - (x==1 ? 0 : 1);
	if (k == 0) return 0;
	if (k == 1) return deg;
	if (deg == 0) return INF;
	return f(kid[x], k-1);
}

void dfs(int x, int p) {
	parent[x] = p;
	kid[x] = 0;

	REP(i, adj[x].size()) {
		int y = adj[x][i];
		if (y != p) {
			sib[y] = kid[x];
			kid[x] = y;
			dfs(y, x);
		}
	}
}

int main() {
	int P;
	scanf("%d %d", &N, &P);
	REP(i, N-1) {
		int x, y;
		scanf("%d %d", &x, &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	kid[0] = sib[0] = parent[0] = 0;
	dfs(1, 0);

	memset(memo, 0xff, sizeof(memo));

	int res = INF;
	for (int x = 1; x <= N; x++)
		res <?= g(x,P) + (x==1 ? 0 : 1);
	printf("%d\n", res);
}
