#include <cstdio>
#include <vector>
using namespace std;

vector<int> adj[1024];
int low[1024], pre[1024], N, T;

void dfs(int x, int parent)
{
	T++;
	low[x] = pre[x] = T;

	for (int i = 0; i < (int)adj[x].size(); i++) {
		int y = adj[x][i];
		if (y == parent)
			continue;

		if (pre[y] == 0) {
			dfs(y, x);
			if (low[y] < low[x]) low[x] = low[y];
			printf("%d %d\n", x, y);
			if (low[y] == pre[y])
				printf("%d %d\n", y, x);
		} else if (pre[y] < pre[x]) {
			printf("%d %d\n", x, y);
			if (pre[y] < low[x])
				low[x] = pre[y];
		}
	}
}


int main()
{
	int M, x, y;
	for (int cs = 1; scanf("%d %d", &N, &M) == 2 && N > 0; cs++) {
		for (int i = 0; i <= N; i++) {
			adj[i].clear();
			pre[i] = 0;
		}

		for (int i = 0; i < M; i++) {
			scanf("%d %d", &x, &y);
			if (x == y) continue;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}

		printf("%d\n\n", cs);
		T = 1;
		dfs(1, -1);
		printf("#\n");		
	}
}
