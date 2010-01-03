#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
using namespace std;

int N, L, K;
char S[100];

char memo[41][16400][41];

int rec(int pos, int i, int o) {
	if (memo[pos][i][o] != 42) return memo[pos][i][o];

	int res = 0;
	if (S[pos] == '0') {
		if (o < K)
			res += rec(pos+1, i, o+1);
	} else {
		int m = 1, x = S[pos]-'0';
		for (; pos+m <= K; x = x * 2 + S[pos+m]-'0', m++) {
			if (pos+m < K && S[pos+m] != '0')
				continue;

			if (m == 2) {
				if (x != 3) continue;
				if (i+2 <= N) res += rec(pos+m, i+2, o);
				if (i+3 <= N) res += rec(pos+m, i+3, o);
			} else {
				if (i+x > N) break;
				res += rec(pos+m, i+x, o);
			}

			if (res > 2) break;
		}
	}

	return memo[pos][i][o] = min(res, 2);
}

int solve() {
	K = strlen(S);

	if (L-N < 0) return 0;
	if (L-N > K) return 0;

	for (int pos = 0; pos < K; pos++)
		for (int i = 0; i <= N; i++)
			for (int o = 0; o <= K; o++)
				memo[pos][i][o] = 42;

	for (int i = 0; i <= N; i++)
		for (int o = 0; o <= K; o++)
			memo[K][i][o] = 0;
	memo[K][N][L-N] = 1;

	return rec(0, 0, 0);
}

int main() {
	for (int cs = 1; scanf("%d %d %s", &L, &N, S) == 3; cs++) {
		if (L == 0 && N == 0) break;

		int res = solve();
		printf("Case #%d: ", cs);
		if (res == 0)
			printf("NO\n");
		else if (res == 1)
			printf("YES\n");
		else
			printf("NOT UNIQUE\n");
	}
}
