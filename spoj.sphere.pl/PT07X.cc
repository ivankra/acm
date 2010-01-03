#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int N;
vector<int> adj[100010];
int memo[100010][2], got[100010][2];

// flag = [is x-p edge covered]
int f(int x, int p, int flag)
{
	if (got[x][flag])
		return memo[x][flag];

	int with = 1, without = 0;
	for (int i = 0; i < (int)adj[x].size(); i++) {
		int y = adj[x][i];
		if (y == p) continue;
		with += f(y, x, 1);
		without += f(y, x, 0);
	}

	got[x][flag] = 1;
	return memo[x][flag] = (flag == 0 ? with : min(with, without));
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
	memset(got, 0, sizeof(got));
	printf("%d\n", f(1, -1, 1));
}
