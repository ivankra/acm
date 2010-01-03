#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

static int f[102][1024], g[102][1024], a[128], n, d, r1, r2, T;

int main()
{
	int i, p, q;

	for (scanf("%d", &T); T-- > 0 && scanf("%d %d", &n, &d) == 2;) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		sort(a, a+n);
		for (i = n-1; i >= 0; i--)
			a[i] = a[i] - a[0];

		for (i = 0; i < 1024; i++) f[n][i] = g[n][i] = 0;

		a[n] = a[n-1];
		for (i = n-1; i >= 0; i--)
			for (p = 0; p <= a[n]; p++) {
				int u = p+d <? a[n];
				f[i][p] = f[i+1][u] + abs(a[i]-p);
				g[i][p] = g[i+1][u] >? abs(a[i]-p);
				if (p > 0) {
					f[i][p] <?= f[i][p-1];
					g[i][p] <?= g[i][p-1];
				}
			}

		printf("%d %d\n", g[0][a[n]], f[0][a[n]]);
	}

	return 0;
}
