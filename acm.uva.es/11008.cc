#include <stdio.h>
#include <string.h>

int bitcnt[65536], memo[65536], x[32], y[32], par[32][32], n, m;

int f(int S) {
	if (memo[S] >= 0) return memo[S];
	if (bitcnt[S] <= m) return memo[S] = 0;
	if (bitcnt[S] <= 2) return memo[S] = 1;
	memo[S] = 1000;
	for (int a = 0; a < n; a++) {
		if ((S & (1 << a)) == 0) continue;
		for (int b = a+1; b < n; b++) {
			if ((S & (1 << b)) == 0) continue;
			if (x[a]==x[b] && y[a]==y[b]) continue;

			memo[S] <?= 1 + f(S & ~par[a][b]);
		}
	}
	return memo[S];
}

int main()
{
	bitcnt[0] = 0;
	for (int i = 1; i < 65536; i++) bitcnt[i] = 1 + bitcnt[i&(i-1)];

	int T;
	scanf("%d", &T);
	for (int cs = 1; cs <= T && scanf("%d %d", &n, &m) == 2; cs++) {
		for (int i = 0; i < n; i++) scanf("%d %d", &x[i], &y[i]);
		memset(memo, 0xff, sizeof(memo));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				par[i][j] = (1 << i) | (1 << j);
				for (int k = 0; k < n; k++)
					if (((x[j]-x[i])*(y[k]-y[i])-(y[j]-y[i])*(x[k]-x[i])) == 0)
						par[i][j] |= 1 << k;
			}
		}
		m = (n - m) >? 0;
		printf("%sCase #%d:\n%d\n", cs==1?"":"\n", cs, f((1<<n)-1));
	}
	return 0;
}
