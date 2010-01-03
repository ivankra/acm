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

enum { MAXN = 100010, MOD = 10007 };

int adjVertex[2*MAXN], adjNext[2*MAXN], adjHead[2*MAXN];
int f[MAXN][2], g[MAXN][2];
int N;

void dfs(int x, int parent)
{
	int with = 1, without = 0;
	int withCnt = 1, withoutCnt = 1;

	for (int i = adjHead[x]; i != 0; i = adjNext[i]) {
		int y = adjVertex[i];
		if (y != parent) {
			dfs(y, x);
			with += f[y][1];
			withCnt = (withCnt * g[y][1]) % MOD;
			without += f[y][0];
			withoutCnt = (withoutCnt * g[y][0]) % MOD;
		}
	}

	f[x][0] = with;
	g[x][0] = withCnt;

	f[x][1] = min(with, without);
	if (with < without)
		g[x][1] = withCnt;
	else if (without < with)
		g[x][1] = withoutCnt;
	else
		g[x][1] = (withCnt + withoutCnt) % MOD;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);

		for (int i = 1; i <= N; i++) adjHead[i] = 0;

		int a = 0, u, v;
		for (int i = 1; i < N; i++) {
			scanf("%d %d", &u, &v);

			++a;
			adjVertex[a] = v;
			adjNext[a] = adjHead[u];
			adjHead[u] = a;

			++a;
			adjVertex[a] = u;
			adjNext[a] = adjHead[v];
			adjHead[v] = a;
		}

		int root = 1;

		dfs(root, -1);
		printf("%d %d\n", f[root][1], g[root][1]);
	}
}
