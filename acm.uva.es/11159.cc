#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>
#include <sstream>
using namespace std;

int N, M, match[128], adj[128][128], seen[128];

int aug(int x) {
	if (seen[x]++) return 0;

	for (int y = 0; y < M; y++) {
		if (adj[x][y] && (match[y] < 0 || aug(match[y]))) {
			match[y] = x;
			return 1;
		}
	}

	return 0;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		long long A[128], B[128];

		scanf("%d", &N);  assert(N<=100);
		for (int i = 0; i < N; i++) {
			scanf("%lld", &A[i]);
			if (A[i] < 0) A[i] = -A[i];
		}

		scanf("%d", &M);  assert(M<=100);
		for (int i = 0; i < M; i++) {
			scanf("%lld", &B[i]);
			if (B[i] < 0) B[i] = -B[i];
		}

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				adj[i][j] = (B[j]==0) || (A[i] != 0 && (B[j] % A[i]) == 0);

		for (int y = 0; y < M; y++) match[y] = -1;

		int res = 0;
		for (int x = 0; x < N; x++) {
			memset(seen, 0, sizeof(seen));
			if (aug(x)) res++;
		}
		printf("Case %d: %d\n", cs, res);
	}
}


