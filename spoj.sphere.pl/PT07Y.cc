#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int N, K;
bool seen[10010];
vector<int> adj[10010];

void dfs(int x) {
	K++;
	seen[x] = true;
	for (int i = 0; i < (int)adj[x].size(); i++) {
		int y = adj[x][i];
		if (!seen[y])
			dfs(y);
	}
}

int main()
{
	int M;
	scanf("%d %d", &N, &M);

	if (M != N-1) {
		printf("NO\n");
		return 0;
	}

	for (int i = 0; i < N-1; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	K = 0;
	memset(seen, 0, sizeof(seen));
	dfs(1);

	if (K != N) {
		printf("NO\n");
	} else {
		printf("YES\n");
	}
}
