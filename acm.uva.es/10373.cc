// knapsack DP
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

int value[300], cost[300];
int f[21][20010], N;

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d %d", &value[i], &cost[i]);

		memset(f, 0x3f, sizeof(f));
		f[0][0] = 0;
		for (int i = 0; i < N; i++) {
			for (int k = min(i+1, 20); k >= 1; k--) {
				for (int c = 1000*k; c >= value[i]; c--) {
					f[k][c] <?= f[k-1][c-value[i]] + cost[i];
				}
			}
		}

		int Q, M, Cmin, Cmax;
		scanf("%d", &Q);

		if (cs != 1) printf("\n");
		for (int q = 1; q <= Q; q++) {
			scanf("%d %d %d", &M, &Cmin, &Cmax);
			int best = 0x3fffffff;
			for (int c = Cmin*M; c <= Cmax*M; c++) {
				best <?= f[M][c];
			}

			if (best <= 1000*M)
				printf("%d\n", best);
			else
				printf("impossible\n");
		}

	}
}
