#include <cstdio>
#include <algorithm>
using namespace std;

int a[5010], f[1500], g[1500], N, K, T;

int main() {
	for (scanf("%d", &T); T-- > 0 && scanf("%d %d", &K, &N) == 2;) {
		K += 8;

		for (int i = 0; i < N; i++) scanf("%d", &a[i]);
		sort(a, a+N);

		for (int i = 0; i < K; i++) f[i] = g[i] = 1<<30;
		f[0] = g[0] = 0;

		for (int i = N-1; i >= 0; i--) {
			for (int k = K; k > 0; k--) {
				int t = f[k];
				if (N-i < 3*k)
					f[k] = 1<<30;
				else
					f[k] <?= g[k-1] + (a[i]-a[i+1])*(a[i]-a[i+1]);
				g[k] = t;
			}
		}

/*		f[i][k] = min(f[i+1][k], (a[i]-a[i+1])^2 + f[i+2][k-1])
		f[i][k] = INF, if N-1-i < 3*k*/
		printf("%d\n", f[K]);
	}
}
