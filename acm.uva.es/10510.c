#include <stdio.h>
#include <assert.h>

#define N 16384

int next[65536], ref[65536], outdeg[N], indeg[N], adj[N], n;
int st[N], fin[N], low[N], valid, tm;

void dfs(int x)
{
	int a, y;

	tm++;
	st[x] = tm;
	low[x] = tm;

	if (outdeg[x] == 1) {
		y = ref[adj[x]];

		if (st[y] != 0) {
			fin[x] = tm;
			low[x] = st[y];
			if (fin[y] != 0) valid = 0;
			return;
		}

		dfs(y);
		fin[x] = tm;
		low[x] = low[y];
		if (low[y] > st[x]) valid = 0;
		return;
	}

	for (a = adj[x]; a != 0; a = next[a]) {
		y = ref[a];
		if (st[y] == 0) {
			dfs(y);
			if (!valid || low[y] > st[x]) { valid = 0; return; }

			if (low[y] != st[x]) {
				if (low[x] != st[x]) { valid = 0; return ;}
				low[x] = low[y];
			}
		} else {
			if (st[y] > st[x]) { valid = 0; return; }

			if (low[x] == st[x]) {
				low[x] = st[y];
			} else {
				valid = 0; return;
			}

		}
	}
	fin[x] = tm;
}

int check()
{
	int i;

	if (n <= 1) return 1;

	for (i = 0; i < n; i++)
		if (indeg[i] != outdeg[i] || outdeg[i] < 1) return 0;

	for (i = 0; i < n; i++)
		st[i] = fin[i] = 0;

	valid = 1;
	tm = 0;

	dfs(0);
	if (valid == 0) return 0;

	for (i = 0; i < n; i++)
		if (st[i] == 0) return 0;

	return valid;
}

int main()
{
	int i, t, m, x, y;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		for (i = 0; i < n; i++)
			adj[i] = indeg[i] = outdeg[i] = 0;

		assert(0 <= n && n < N && 0 <= m && m < 32768);
		for (i = 1; m-- > 0 && scanf("%d %d", &x, &y) == 2;) {
			assert(0 <= x && x < n && 0 <= y && y < n && x != y);
			ref[i] = y; next[i] = adj[x]; adj[x] = i++;
			outdeg[x]++; indeg[y]++;
		}

		printf(check() ? "YES\n" : "NO\n");
	}

	return 0;
}
