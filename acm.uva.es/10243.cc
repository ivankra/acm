#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <map>
using namespace std;

int deg[1024], adj[1024][1024], memo[1024][2], N;

int doit(int x, int p, int flag) {
	int &res = memo[x][flag];
	if (res >= 0)
		return res;

	if (flag == 1) {
		res = 1;
		for (int i = 0; i < deg[x]; i++) {
			int y = adj[x][i];
			if (y != p) {
				res += min(doit(y, x, 0), doit(y, x, 1));
			}
		}
	} else {
		res = 0;
		for (int i = 0; i < deg[x]; i++) {
			int y = adj[x][i];
			if (y != p) {
				res += doit(y, x, 1);
			}
		}
	}

	return res;
}

int main()
{
	while (scanf("%d", &N) == 1 && N > 0) {
		for (int i = 1; i <= N; i++) {
			scanf("%d", &deg[i]);
			for (int j = 0; j < deg[i]; j++)
				scanf("%d", &adj[i][j]);
		}
		memset(memo, 0xff, sizeof(memo));
		int best = doit(1, -1, 1);
		if (N > 1)
			best = min(best, doit(1, -1, 0));
		printf("%d\n", best);
	}
}
