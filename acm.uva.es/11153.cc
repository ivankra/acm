#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

int MaxCost, MaxTime, N, Fee[16], Fun[16];
int dist[16][16];

int f[13][1<<13];

int solve()
{
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				dist[i][j] <?= dist[i][k] + dist[k][j];

	//memset(f, 0x3f, sizeof(f));

	for (int x = 0; x < N; x++)
		f[x][0] = dist[x][0];

	for (int m = 2; m < (1 << N); m += 2) {
		for (int x = 0; x < N; x++) {
			f[x][m] = 1<<20;
			for (int y = 1; y < N; y++)
				if (m & (1 << y))
					f[x][m] <?= dist[x][y] + f[y][m^(1<<y)];
		}
	}

	int best = 0;
	for (int m = 0; m < (1 << N); m += 2) {
		int tim = f[0][m];
		if (tim > MaxTime) continue;

		int cost = 0;
		int fun = 0;

		for (int i = 1; i < N; i++) {
			if (m & (1 << i)) {
				tim += 15;
				cost += Fee[i];
				fun += Fun[i];
			}
		}

		if (cost > MaxCost || tim > MaxTime)
			continue;

		best = max(best, fun);
	}

	return best;
}

int main()
{
	int T, nroads;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d %d", &MaxCost, &MaxTime, &N, &nroads);

		N++;
		assert(N <= 13);

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				dist[i][j] = (i == j ? 0 : (1<<20));

		for (int i = 1; i < N; i++)
			scanf("%d %d", &Fee[i], &Fun[i]);

		for (int i = 0; i < nroads; i++) {
			int x, y, z;
			scanf("%d %d %d", &x, &y, &z);
			if (z < dist[x][y])
				dist[x][y] = dist[y][x] = z;
		}

		int res = solve();
		printf("Case %d: ", cs);

		if (res <= 0)
			printf("No possible trip.\n");
		else
			printf("%d\n", res);
	}
}
