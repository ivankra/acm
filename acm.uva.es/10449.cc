#include <cstdio>
#include <cassert>

long long b[256], d[256][256], INF=1LL<<60, NINF=-INF;
int r[256][256];

int main() {
	int N, M, x, y;
	for (int cs = 1; scanf("%d", &N) == 1; cs++) {
		for (int i = 1; i <= N; i++) scanf("%lld", &b[i]);

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				d[i][j] = INF;
				r[i][j] = 0;
			}
			d[i][i] = 0;
			r[i][i] = 0;
		}

		scanf("%d", &M);
		for (int i = 0; i < M && scanf("%d %d", &x, &y) == 2; i++) {
			d[x][y] = (b[y]-b[x])*(b[y]-b[x])*(b[y]-b[x]);
			r[x][y] = 1;
		}

		for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++) if (r[i][k])
		for (int j = 1; j <= N; j++) {
			if (r[k][j]) {
				r[i][j] = 1;
				d[i][j] <?= d[i][k] + d[k][j];
				if (d[i][j] < NINF) d[i][j] = NINF;
			}
		}

		for (int i = 1; i <= N; i++) {
			b[i] = d[1][i];
			if (!r[1][i]) {
				b[i] = -1;
				continue;
			}
			for (int j = 1; j <= N; j++)
				if (r[1][j] && d[j][j] < 0 && r[j][i]) {
					b[i] = -1;
					break;
				}
		}

		printf("Set #%d\n", cs);

		scanf("%d", &M);
		while (M-- > 0 && scanf("%d", &x) == 1)
			printf(b[x]<3 ? "?\n" : "%lld\n", b[x]);
	}
}
