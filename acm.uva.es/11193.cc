#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <set>
using namespace std;

int cost[256];

int reduce(int *v, int N, int pri, int sec) {
	if (N <= 1) return v[0];

	const int INF = 0x3fffffff;

	static int f[512][512];
	for (int i = 0; i < N; i++) {
		f[1][i] = v[i] >= 0 ? v[i] : INF;
	}

	for (int len = 2; len <= N; len++) {
		for (int s = 0; s+len <= N; s++) {
			f[len][s] = INF;

			if (v[s+len-1] < 0)
				f[len][s] <?= max(f[len-1][s], -v[s+len-1]-1) + sec;

			for (int m = 1; m < len; m++)
				f[len][s] <?= max(f[m][s], f[len-m][s+m]) + pri;
		}
	}

	return f[N][0];
}

int expr(int level = 0) {
	char ch;
	if (level < 2) {
		char primary = (level == 0 ? '+' : '*');
		char secondary = (level == 0 ? '-' : '/');

		int v[512], n = 0;
		v[n++] = expr(level + 1);

		for (;;) {
			if (scanf(" %c", &ch) != 1) break;
			if (ch == primary) {
				v[n++] = expr(level + 1);
			} else if (ch == secondary) {
				v[n++] = -1 - expr(level + 1);
			} else {
				ungetc(ch, stdin);
				break;
			}
		}

		return reduce(v, n, cost[primary], cost[secondary]);
	} else {
		scanf(" %c", &ch);
		if (ch == '(') {
			int res = expr(0);
			scanf(" )");
			return res;
		}

		ungetc(ch, stdin);
		scanf(" %*d");
		return 0;
	}
}

int main() {
	while (scanf("%d %d %d %d", &cost['+'], &cost['-'], &cost['*'], &cost['/']) == 4) {
		if (cost['+'] == 0 && cost['-'] == 0 && cost['*'] == 0 && cost['/'] == 0) break;
		printf("%d\n", expr());
	}
}
