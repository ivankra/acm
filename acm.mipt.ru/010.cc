#include <cstdio>
#include <vector>
using namespace std;

int n, m, match[1010], seen[1010];
vector<int> adj[1010];

int dfs(int y) {
	if (seen[y]++) return 0;
	for (int i = 0; i < (int)adj[y].size(); i++) {
		int x = adj[y][i];
		if (match[x] < 0 || dfs(match[x])) {
			match[x] = y;
			return 1;
		}
	}
	return 0;
}

int main()
{
	int e, x, y;
	scanf("%d %d %d", &n, &m, &e);
	while (e-- > 0 && scanf("%d %d", &x, &y) == 2)
		adj[y-1].push_back(x-1);

	memset(match, 0xff, sizeof(match));
	int res = 0;
	for (y = 0; y < m; y++) {
		memset(seen, 0, sizeof(seen));
		if (dfs(y)) res++;
	}

	printf("%d\n", res);
	for (x = 0; x < n; x++)
		if (match[x] >= 0) printf("%d %d\n", x+1, match[x]+1);
}
