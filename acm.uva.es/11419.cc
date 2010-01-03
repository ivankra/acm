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
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long LL;
#define FOREACH(it, v) for(typeof((v).begin())it=(v).begin();it!=(v).end();++it)
#define SIZE(v) ((int)(v).size())
#define ALL(v) (v).begin(), (v).end()
#define REP(i,n) for(int i=0;i<(n);++i)

char adj[1024][1024];
int N, M, xmatch[1024], ymatch[1024], xseen[1024], yseen[1024];

void dfs2(int x)
{
	if (xseen[x]) return;
	xseen[x] = 1;

	for (int y = 0; y < M; y++) {
		if (!adj[x][y]) continue;
		yseen[y] = 1;
		if (ymatch[y] != -1) dfs2(ymatch[y]);
	}
}

int dfs(int x)
{
	if (xseen[x] == 0) {
		xseen[x] = 1;
		for (int y = 0; y < M; y++) {
			if (adj[x][y] && (ymatch[y] == -1 || dfs(ymatch[y]))) {
				xmatch[x] = y;
				ymatch[y] = x;
				return 1;
			}
		}
	}
	return 0;
}

int main()
{
	int x, y, e;
	while (scanf("%d %d %d", &N, &M, &e) == 3) {
		if (N <= 0 || M <= 0) break;

		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < e; i++) {
			scanf("%d %d", &x, &y);
			x--; y--;
			adj[x][y] = 1;
		}

		int flow = 0;
		memset(xmatch, 0xff, sizeof(xmatch));
		memset(ymatch, 0xff, sizeof(ymatch));

		for (x = 0; x < N; x++) {
			memset(xseen, 0, sizeof(int) * N);
			if (dfs(x)) flow++;
		}

		memset(xseen, 0, sizeof(xseen));
		memset(yseen, 0, sizeof(yseen));
		for (x = 0; x < N; x++)
			if (xmatch[x] == -1) dfs2(x);

		printf("%d", flow);
		for (x = 0; x < N; x++)
			if (!xseen[x]) printf(" r%d", x+1);
		for (y = 0; y < M; y++)
			if (yseen[y]) printf(" c%d", y+1);
		printf("\n");
	}
}
