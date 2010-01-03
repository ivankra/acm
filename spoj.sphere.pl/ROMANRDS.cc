#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
typedef long long LL;
const double PI = 2 * acos(0.0);

bool adj[512][512];
int N, seen[1000], cityId;
pair<int, int> res[1000];

vector<int> vadj[1000];

int vdfs(int x, int prevEdge)
{
	if (seen[x]) return 0;
	seen[x] = 1;

	for (int i = 0; i < (int)vadj[x].size(); i++) {
		int e = vadj[x][i];
		if (e == prevEdge) continue;

		if (res[e].first != x && res[e].second != x) return 0;
		int y = res[e].first == x ? res[e].second : res[e].first;
		if (y == x) return 0;

		if (!vdfs(y, e)) return 0;
	}

	return 1;
}

int dfs2(int x, int common, int prev)
{
//printf("dfs2:  --%d---(city %d)---%d--\n", prev+1, common, x+1);

	assert(!seen[x]);
	seen[x] = 1;
	res[x].first = common;
	res[x].second = ++cityId;

	for (int y = 0; y < N; y++) {
		if (y == prev || !adj[x][y]) continue;
		if (adj[y][prev]) continue;
		if (seen[y]) return 0;
		if (!dfs2(y, res[x].second, x)) return 0;
	}

	return 1;
}

int solveGeneric(vector<int> S)
{
	for (int x = 0; x < N; x++) {
		if (x == S[0] || x == S[1] || x == S[2]) continue;

		int cnt = 0;
		for (int i = 0; i < (int)S.size(); i++) {
			if (adj[x][S[i]]) cnt++;
		}
		if (cnt <= 1) continue;

		if (cnt != (int)S.size()) return 0;
		S.push_back(x);
	}

//printf("S="); for(int i = 0; i < (int)S.size(); i++) printf(" %d", S[i]+1);printf("\n");

	memset(res, 0, sizeof(res));

	cityId = 1;
	memset(seen, 0, sizeof(seen));
	for (int i = 0; i < (int)S.size(); i++) {
		int x = S[i];
		seen[x] = 1;
		res[x].first = 1;
		res[x].second = ++cityId;
	}

	for (int x = 0; x < N; x++) {
		if (seen[x]) continue;

		int y = -1, cnt = 0;
		for (int i = 0; i < (int)S.size(); i++)  {
			if (adj[x][S[i]]) {
				y = S[i];
				cnt++;
			}
		}
		if (cnt == 0) continue;

//printf("x=%d cnt=%d [y=%d]\n",x+1,cnt,y+1);
		if (cnt != 1) return 0;

		if (!dfs2(x, res[y].second, y)) return 0;
	}

	for (int i = 0; i < N; i++) {
		vadj[res[i].first].push_back(i);
		vadj[res[i].second].push_back(i);
	}
	memset(seen, 0, sizeof(seen));
	if (!vdfs(1, -1)) return 0;

	printf("YES\n");
	for (int i = 0; i < N; i++) {
		printf("%d %d\n", res[i].first, res[i].second);
	}
	return 1;
}

int solveChain()
{
	int cnt1 = 0, cnt2 = 0, cur = -1;
	for (int x = 0; x < N; x++) {
		int deg = 0;
		for (int y = 0; y < N; y++) {
			if (adj[x][y]) deg++;
		}
		if (deg == 1) {
			cur = x;
			cnt1++;
		} else if (deg == 2) {
			cnt2++;
		} else {
			return 0;
		}
	}
	if (cnt1 != 2) return 0;

	int next = -1, prev = -1;
	int id = 1;

	while (cur != -1) {
		res[cur] = make_pair(id, id+1);
		id++;

		next = -1;
		for (int x = 0; x < N; x++) {
			if (x != prev && adj[x][cur]) next = x;
		}
		prev = cur;
		cur = next;
	}

	printf("YES\n");
	for (int i = 0; i < N; i++) {
		printf("%d %d\n", res[i].first, res[i].second);
	}
	return 1;
}

void dfs(int x) {
	if (seen[x]) return;
	seen[x] = 1;
	for (int y = 0; y < N; y++)
		if (adj[x][y]) dfs(y);
}

int solve()
{
	// check connectivity
	memset(seen, 0, sizeof(seen));
	dfs(0);
	for (int i = 0; i < N; i++)
		if (!seen[i]) return 0;

	// single edge
	if (N == 1) {
		printf("YES\n1 2\n");
		return 1;
	}

	// generic tree with a 3+ degree vertex
	for (int a = 0; a < N; a++) {
		for (int b = a+1; b < N; b++) {
			for (int c = b+1; c < N; c++) {
				if (adj[a][b] && adj[b][c] && adj[a][c]) {
					vector<int> S;
					S.push_back(a);
					S.push_back(b);
					S.push_back(c);
					return solveGeneric(S);
				}
			}
		}
	}

	// simple chain
	return solveChain();
}

int main()
{
	memset(adj, 0, sizeof(adj));
	scanf("%d", &N);
	for (int x = 0; x < N; x++) {
		int d, y;
		scanf("%d", &d);
		for (int i = 0; i < d; i++) {
			scanf("%d", &y);
			y--;
			if (x == y || y < 0 || y >= N) { printf("NO\n"); exit(0); }
			adj[x][y] = adj[y][x] = 1;
		}
	}

	if (!solve()) {
		printf("NO\n");
	}
}
