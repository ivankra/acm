#include <stdio.h>

#define MAXN 16

int cost[MAXN][MAXN], split[MAXN][MAXN];    /* [length][offset] */
int dim[MAXN][2], n;

void print(int k, int p)
{
	if (k == 1) {
		printf("A%d", p + 1);
	} else {
		putchar('(');
		print(split[k][p], p);
		printf(" x ");
		print(k - split[k][p], p + split[k][p]);
		putchar(')');
	}
}

void solve()
{
	int i, j, k, m;

	for (i = 0; i < n; i++)
		cost[1][i] = 0;

	for (k = 2; k <= n; k++) {
		for (i = n - k; i >= 0; i--) {
			cost[k][i] = 0x0FFFFFFF;

			for (j = k - 1; j >= 1; j--) {
				m = cost[j][i] + cost[k - j][i + j] +
				    dim[i][0] * dim[i+j][0] * dim[i+k-1][1];

				if (m >= cost[k][i])
					continue;

				cost[k][i] = m;
				split[k][i] = j;
			}
		}
	}
}

int main()
{
	int i, t;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &dim[i][0], &dim[i][1]);

		solve();

		printf("Case %d: ", t);
		print(n, 0);
		printf("\n");
	}

	return 0;
}
