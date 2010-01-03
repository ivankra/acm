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

int demand[32], d[32][32], N;
int jobs[300], sum[300], K, bound;

set<int> seen;

int go(int i, int a, int b, int c) {
	if (b < c) swap(b, c);
	if (a < b) swap(a, b);
	if (b < c) swap(b, c);

	if (a > bound) return false;
	if (i >= K) return true;

	if (a-b > jobs[K-1]) return false;
	if (b-c > jobs[K-1]) return false;

	int key = (i * 1201 + a) * 1201 + b;
	if (seen.count(key) != 0) return false;
	seen.insert(key);

	if (go(i+1, a, b, c+jobs[i])) return true;
	if (go(i+1, a, b+jobs[i], c)) return true;
	if (go(i+1, a+jobs[i], b, c)) return true;

	return false;
}

long long solve() {
	if (N < 2) return 0;

	K = 0;
	for (int i = 2; i <= N; i++) {
		if (demand[i] > 0 && 2*d[1][i] > 1200) return -1;
		for (int j = 0; j < demand[i]; j++) {
			assert(K <= 201);
			jobs[K++] = 2 * d[1][i];
		}
	}

	sort(jobs, jobs+K);

	sum[0] = 0;
	for (int i = 1; i <= K; i++)
		sum[i] = sum[i-1] + jobs[i-1];

#if 0
	printf("jobs:");
	for (int i = 0; i < K; i++) printf(" %d", jobs[i]);
	printf("\n");
#endif

	int left = 0, right = 1201;
	while (left < right) {
		bound = (left + right) / 2;
		seen.clear();
//		printf("trying bound=%d\n",bound);
		if (bound <= 1200 && go(0, 0, 0, 0))
			right = bound;
		else
			left = bound + 1;
	}

	return left;
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d", &N) == 1; cs++) {
		assert(N <= 30);
		memset(demand, 0, sizeof(demand));
		for (int i = 2; i <= N; i++) scanf("%d", &demand[i]);

		for (int i = 0; i < 32; i++)
			for (int j = 0; j < 32; j++)
				d[i][j] = (i == j ? 0 : 999999);

		int u, v, c;
		while (scanf("%d %d %d", &u, &v, &c) == 3 && u > 0) {
			d[u][v] <?= c;
			d[v][u] <?= c;
		}

		for (int k = 1; k <= N; k++)
			for (int i = 1; i <= N; i++)
				for (int j = 1; j <= N; j++)
					d[i][j] <?= d[i][k] + d[k][j];

		int res = solve();

		printf("Test Case #: %d\n", cs);
		if (res < 0 || res > 1200)
			printf("Too few trucks\n");
		else
			printf("%d mins\n", res);
	}
}
