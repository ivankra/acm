#include <cstdio>
#include <cstring>
#define oo 0x3fffffff

int main()
{
	int d[16][16], c[16][16][32], n, k, a[16][16], b[16][16];
	for (int cs=1; scanf("%d %d", &n, &k) == 2 && n > 0; cs++) {
		printf("Scenario #%d\n", cs);
		for (int i = 0; i < n; i++) {
			d[i][i] = 1; c[i][i][0] = 0;
			for (int j = 0; j < n; j++) {
				a[i][j] = (i==j) ? 0 : oo;
				if (i == j) continue;
				scanf("%d", &d[i][j]);
				for (int t = 0; t < d[i][j]; t++)
					scanf("%d", &c[i][j][t]);
			}
		}

		for (int m = 0; m < k; m++) {
			for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				b[i][j] = oo;
				for (int t = 0; t < n; t++)
					if (c[t][j][m%d[t][j]] > 0)
						b[i][j] <?= a[i][t] + 
							    c[t][j][m%d[t][j]];				}
			memcpy(a, b, sizeof(b));
		}

		printf(a[0][n-1] < oo ? "The best flight costs %d.\n\n"
				      : "No flight possible.\n\n", a[0][n-1]);
	}
}
