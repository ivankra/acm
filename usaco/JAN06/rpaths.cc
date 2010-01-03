/*
TASK: rpaths
ID: infnty1
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef vector<int> VI;

int ex[16384], ey[16384], n, m, r;
VI adj[16384];

int dt[16384], dl[16384], T, L[16384], seen[16384];

int dfs2(int p, int x)
{
	int r = 0;
	if (seen[x]++) return 0;
	for (int i = 0; i < adj[x].size(); i++) {
		int y = adj[x][i];
		if (y == p) continue;

		if (dl[y] != dl[x]) r++;

		if (!seen[y])
			r += dfs2(x, y);
	}
	if (dt[x] == dl[x] && r == 0) L[x] = 1;
	return r;
}

void dfs(int p, int x)
{
	if (dt[x] > 0) return;
	dt[x] = dl[x] = ++T;
	for (int i = 0; i < adj[x].size(); i++) {
		int y = adj[x][i];
		if (y == p) continue;

		if (dt[y] > 0)
			dl[x] <?= dt[y];
		else {
			dfs(x, y);
			dl[x] <?= dl[y];
		}
	}
}

int main()
{
	int i;

	freopen("rpaths.in", "r", stdin);
	freopen("rpaths.out", "w", stdout);

	scanf("%d %d", &n, &m);
	for (i = 0; i < m; i++) {
		scanf("%d %d", &ex[i], &ey[i]);
		adj[ex[i]].push_back(ey[i]);
		adj[ey[i]].push_back(ex[i]);
	}

	memset(dt, 0, sizeof(dt));
	T = 0;
	dfs(0, 1);

	memset(L, 0, sizeof(L));
	memset(seen, 0, sizeof(seen));
	dfs2(0, 1);

	for (i = 2; i <= n && !L[i]; i++);

	memset(seen, 0, sizeof(seen));
	dfs2(0, i);

	T = 0;
	for (i = 1; i <= n; i++) T += L[i];

	printf("%d\n", (T+1)/2);

	return 0;
}
