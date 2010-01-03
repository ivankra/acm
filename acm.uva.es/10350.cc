#include <cstdio>
#include <cstring>

int n, m, f[128][16], dist[128][16][16];

int main() {
	char s[1000];
	while (scanf(" %s %d %d", s, &n, &m) == 3) {
		for (int i = 0; i < n-1; i++)
			for (int j = 0; j < m; j++)
				for (int k = 0; k < m; k++)
					scanf("%d", &dist[i][j][k]);

		memset(f, 0, sizeof(f));

		for (int k = n-2; k >= 0; k--) {
			for (int i = 0; i < m; i++) {
				f[k][i] = 1<<30;
				for (int j = 0; j < m; j++)
					f[k][i] <?= dist[k][i][j] + 2 + f[k+1][j];
			}
		}

		int res = 1<<30;
		for (int i = 0; i < m; i++) res <?= f[0][i];

		printf("%s\n%d\n", s, res);
	}

}
