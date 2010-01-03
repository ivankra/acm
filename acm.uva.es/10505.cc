#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N, adj[256][256], seen[256];

void dfs(int x, int &a, int &b, int &ok, int col) {
	if (seen[x] != 0) {
		ok &= seen[x] == col;
		return;
	} else {
		seen[x] = col;
		a++;
		for (int y = 0; y < N; y++)
			if (adj[x][y]) dfs(y, b, a, ok, 3-col);
	}
}

int main() {
	int T;
	scanf("%d", &T);

	while (T-- > 0 && scanf("%d", &N) == 1) {
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < N; i++) {
			int k, j;
			scanf("%d", &k);
			while (k-- > 0 && scanf("%d", &j) == 1) {
				j--;
				if (0 <= j && j < N) adj[i][j] = adj[j][i] = 1;
			}
		}

		memset(seen, 0, sizeof(seen));
		int res = 0;
		for (int i = 0; i < N; i++) {
			if (!seen[i]) {
				int a = 0, b = 0, ok = 1;
				dfs(i, a, b, ok, 1);
				res += ok*max(a, b);
			}
		}
		printf("%d\n", res);
	}
}
