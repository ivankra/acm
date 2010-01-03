/*
ID: infnty1
PROB: nocows
LANG: C++
*/
#include <cstdio>
#include <cstring>

// f[n][k] = n nodes, height exactly k
// g[n][k] = n nodes, height less than k
int f[201][101], g[201][101];

int main() {
	freopen("nocows.in", "r", stdin);
	freopen("nocows.out", "w", stdout);

	int N, K;
	scanf("%d %d", &N, &K);

	memset(f, 0, sizeof(f));
	f[1][1] = 1;

	memset(g, 0, sizeof(g));
	for (int k = 2; k <= K; k++) g[1][k] = 1;

	for (int n = 2; n <= N; n++) {
		for (int k = 1; k <= K; k++) {
			f[n][k] = 0;
			for (int l = 1; l <= n-2; l++) {
				int r = n-1-l;
				f[n][k] += f[l][k-1] * f[r][k-1];
				f[n][k] += f[l][k-1] * g[r][k-1];
				f[n][k] += g[l][k-1] * f[r][k-1];
				f[n][k] %= 9901;
			}
		}

		g[n][0] = 0;
		for (int k = 1; k <= K; k++)
			g[n][k] = (g[n][k-1] + f[n][k-1]) % 9901;
	}

	printf("%d\n", f[N][K] % 9901);
}
