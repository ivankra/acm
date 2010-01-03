#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N, adj[256][256], seen[256];

bool dfs(int x, int &a, int &b, int col) {
	if (seen[x] >= 0)
		return seen[x] == col;

	seen[x] = col;
	a++;
	for (int y = 0; y < N; y++)
		if (adj[x][y] && !dfs(y, b, a, col?0:1)) return false;
	return true;
}

int main() {
	int T, M;
	scanf("%d", &T);

	while (T-- > 0 && scanf("%d %d", &N, &M) == 2) {
		memset(adj, 0, sizeof(adj));
		int x, y;
		while (M-- > 0 && scanf("%d %d", &x, &y) == 2)
			adj[x][y] = adj[y][x] = 1;

		int res = 0;
		memset(seen, 0xff, sizeof(seen));

		for (int i = 0; res >= 0 && i < N; i++) {
			if (adj[i][i]) {
				if (seen[i] < 0) {
					int a = 0, b = 0;
					if (!dfs(i, a, b, 1)) { res = -1; break; }
					res += a;
				} else {
					if (seen[i] != 1) { res = -1; break; }
				}
			}
		}

		for (int i = 0; res >= 0 && i < N; i++) {
			if (seen[i] < 0) {
				int a = 0, b = 0;
				if (!dfs(i, a, b, 1)) { res = -1; break; }

				if (a == 0) res += b;
				else if (b == 0) res += a;
				else res += min(a, b);
			}
		}

		printf("%d\n", res);
	}
}
