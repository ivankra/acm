#include <cstdio>
#include <vector>
#define INF 0x1fffffff
using namespace std;

int main()
{
	static int d[128][128], ex[65536], ey[65536], R[128][128];
	int n, m, T;

	scanf("%d", &T);
	for (int cs = 1; cs <= T && scanf("%d %d", &n, &m) == 2; cs++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				d[i][j] = INF;
			d[i][i] = 0;
		}

		for (int i = 0; i < m && scanf("%d %d", &ex[i], &ey[i]) == 2; i++)
			d[ex[i]][ey[i]] = d[ey[i]][ex[i]] = 1;

		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				if (d[i][k] == INF) continue;
				for (int j = i+1; j < n; j++)
					if (d[i][k]+d[k][j] < d[i][j])
						d[j][i] = d[i][j] = d[i][k] + d[k][j];
			}
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				R[i][j] = 0;

		static int votes[128][128];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				votes[i][j] = 0;

		for (int e = 0; e < m; e++)
			for (int x = 0; x < n; x++) {
				if (d[x][ex[e]] + 1 == d[x][ey[e]])
					votes[x][ey[e]]++;

				if (d[x][ey[e]] + 1 == d[x][ex[e]])
					votes[x][ex[e]]++;
			}

		for (int x = 0; x < n; x++) {
			for (int z = 0; z < n; z++) {
				if (votes[x][z] == 0) continue;
				for (int y = 0; y < n; y++)
					if (d[x][z] + d[z][y] == d[x][y])
						R[x][y] += votes[x][z];
			}
		}

		int best = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				best >?= R[i][j];
		printf("Case #%d: %d\n", cs, best);
	}

	return 0;
}
