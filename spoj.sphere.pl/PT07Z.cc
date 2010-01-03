#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int N, best = 0;
vector<int> adj[10010];

int dfs(int x, int p)
{
	int a = 0, b = 0;
	for (int i = 0; i < (int)adj[x].size(); i++) {
		int y = adj[x][i];
		if (y == p) continue;
		int t = 1 + dfs(y, x);
		if (t >= a) { b = a; a = t; }
		else if (t > b) { b = t; }
	}
	best = max(best, a + b);
	return a;
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N-1; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs(1, -1);
	printf("%d\n", best);
}
