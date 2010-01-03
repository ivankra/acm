#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

int n, m, adj[128][6], which[128], seen[128], lft[8];

int dfs(int x) {
	if (seen[x]++) return 0;

	for (int y = 0; y < 6; y++) {
		if (!adj[x][y]) continue;

		if (lft[y] > 0) {
			which[x] = y;
			lft[y]--;
			return 1;
		}

		for (int z = 0; z < m; z++) {
			if (which[z] == y && dfs(z)) {
				which[x] = y;
				return 1;
			}
		}
	}

	return 0;
}

int main() {
	int T, n;
	for (scanf("%d", &T); T-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < 2; j++) {
				char s[16];
				string t[]={"XXL","XL","L","M","S","XS"};
				scanf(" %s", s);
				adj[i][find(t,t+6,s)-t] = 1;
			}
		}

		for (int i = 0; i < 6; i++)
			lft[i] = n/6;

		int i;
		memset(which, 0xff, sizeof(which));
		for (i = 0; i < m; i++) {
			memset(seen, 0, sizeof(seen));
			if (!dfs(i)) break;
		}
		printf(i < m ? "NO\n" : "YES\n");
	}
}
