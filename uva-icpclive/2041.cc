#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> VI;  typedef vector<VI> VVI;

int n;
VVI G; VI col, match, seen;

int mdfs(int x) {
	if (seen[x]++) return 0;
	for (int i = 0; i < (int)G[x].size(); i++) {
		int y = G[x][i];
		if (match[y] < 0 || mdfs(match[y])) {
			match[y] = x; match[x] = y;
			return 1;
		}
	}
	return 0;
}

void dfs(int x) {
	if (col[x] < 0) col[x] = 0;
	for (int i = 0; i < (int)G[x].size(); i++) {
		int y = G[x][i];
		if (col[y] < 0) {
			col[y] = 1 - col[x];
			dfs(y);
		}
		assert(col[y] == 1 - col[x]);
	}
}

int main() {
	while (scanf("%d", &n) == 1) {
		G.assign(n, VI());
		for (int i = 0; i < n; i++) {
			int x, y, m;
			scanf(" %d : ( %d )", &x, &m);
			while (m-- > 0 && scanf("%d", &y) == 1) {
				assert(0 <= x && x < n && 0 <= y && y < n);
				G[x].push_back(y);
			}
		}
		col.assign(n, -1);
		for (int x = 0; x < n; x++)
			if (col[x] < 0) dfs(x);

		int res = n;
		match.assign(n, -1);
		for (int x = 0; x < n; x++) {
			if (col[x] != 0) continue;
			seen.assign(n, 0);
			if (mdfs(x)) res--;
		}
		printf("%d\n", res);
	}
}
