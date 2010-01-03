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
using namespace std;

int need[100], N;
long long memo[50][50];

long long f(int i, int o) {
	if (i > 2*N) return o == 0 ? 1 : 0;
	if (memo[i][o] != -1) return memo[i][o];
	return memo[i][o] = f(i+1, o+1) + (need[i] || o == 0 ? 0 : f(i+1, o-1));
}

int main()
{
	int T, K;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &N, &K);
		memset(need, 0, sizeof(need));
		for (int i = 0; i < K; i++) {
			int x;
			scanf("%d", &x);
			need[x] = 1;
		}
		memset(memo, 0xff, sizeof(memo));
		printf("%lld\n", f(1, 0));
	}
}
