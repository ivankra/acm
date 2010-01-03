#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define NINF (-(1<<20))

int color[201], next[201], N;
int f[201][201], g[201][201][201], g_max[201][201];

int solve()
{
	next[N] = N;
	for (int i = 0; i < N; i++)
		for (next[i] = i+1; next[i] < N && color[next[i]] != color[i]; next[i]++);

	for (int a = 0; a <= N; a++) {
		f[0][a] = 0;
		g_max[0][a] = NINF;
		for (int k = 1; k <= N; k++)
			g[0][a][k] = NINF;
	}

	for (int len = 1; len <= N; len++) {
		for (int a = 0; a+len <= N; a++) {
			int b = a + len - 1;

			if (len == 1) {
				f[len][a] = 1;
				for (int k = 2; k <= len; k++)
					g[len][a][k] = NINF;
				g[len][a][1] = 0;
				g_max[len][a] = 0;
				continue;
			}

			g[len][a][1] = f[len-1][a+1];
			for (int k = 2; k <= len; k++) {
				g[len][a][k] = NINF;
				for (int c = next[a]; c <= b && k-1 <= len-(c-a); c = next[c]) {
					g[len][a][k] >?= f[c-a-1][a+1] + g[len-(c-a)][c][k-1];
				}
			}

			g_max[len][a] = NINF;
			for (int k = 1; k <= len; k++)
				g_max[len][a] >?= k*k + g[len][a][k];

			f[len][a] = NINF;
			for (int m = 1; m <= len; m++)
				f[len][a] >?= g_max[m][a] + f[len-m][a+m];
		}
	}

	return f[N][0];
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		assert(1 <= N && N <= 200);
		for (int i = 0; i < N; i++)
			scanf("%d", &color[i]);
		printf("Case %d: %d\n", cs, solve());
	}
}
