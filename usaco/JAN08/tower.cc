/*
ID: infnty1
LANG: C++
TASK: tower
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define INF 0x1fffffff

int N;
vector<int> adj[10010];
map<long long, int> memo;

int f(int x, int i, int xcov, int parent)
{
	if (i < (int)adj[x].size() && adj[x][i] == parent) i++;

	long long key = (x * 100000LL + i) * 3 + xcov;
	if (memo.count(key) != 0)
		return memo[key];

	int &res = memo[key];
	if (i == (int)adj[x].size()) {
		res = xcov == 0 ? INF : 0;
	} else {
		int y = adj[x][i];
		res = INF;
		res = min(res, f(y,0, xcov==2?1:0, x) + f(x,i+1, xcov, parent));
		res = min(res, 1 + f(y,0, 2, x) + f(x,i+1, xcov==2?2:1, parent));
	}

	return res;
}

int main()
{
	freopen("tower.in", "r", stdin);
	freopen("tower.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 0; i < N-1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	if (N <= 1) {
		printf("1\n");
	} else {
		memo.clear();
		int res = min(f(1,0,0,-1), 1 + f(1,0,2,-1));
		printf("%d\n", res);
	}
}
