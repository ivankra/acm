/*
ID: infnty1
PROB: theme
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
	int a[5010], f[5010], g[5010], N, best=0;

	freopen("theme.in", "r", stdin);
	freopen("theme.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", &a[i]);

	memset(f, 0, sizeof(f));
	for (int i = N-2; i >= 0; i--) {
		for (int j = N-2; j > i; j--) {
			if (a[j+1] - a[i+1] == a[j] - a[i]) {
				g[j] = 1 + f[j+1];
				best = max(best, min(1 + g[j], j - i));
			} else {
				g[j] = 0;
			}
		}
		for (int j = 0; j < N; j++) f[j] = g[j];
	}

	printf("%d\n", best >= 5 ? best : 0);
}
