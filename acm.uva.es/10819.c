#include <stdio.h>
#include <string.h>

int rf[128][16384], rc[128][16384], tp[128], tf[128];
int money, n;

int solve()
{
	int i, k, m, c1, f1;

	m = money + 202;

	for (i = 0; i < m; i++)
		rf[0][i] = rc[0][i] = 0;

	for (k = 1; k <= n; k++) {
		for (i = 0; i < m; i++) {
			rf[k][i] = rf[k - 1][i];
			rc[k][i] = rc[k - 1][i];
		}

		for (i = tp[k]; i < m; i++) {
			f1 = rf[k - 1][i - tp[k]] + tf[k];
			c1 = rc[k - 1][i - tp[k]] + tp[k];

			if (f1 > rf[k][i]) {
				rf[k][i] = f1;
				rc[k][i] = c1;
			} else if (f1 == rf[k][i] && c1 > rc[k][i]) {
				rc[k][i] = c1;
			}
		}
	}

	if (rc[n][money + 200] > 2000)
		return rf[n][money + 200];
	else
		return rf[n][money];
}

int main()
{
	int i;

	while (scanf("%d %d", &money, &n) == 2) {
		for (i = 1; i <= n; i++)
			scanf("%d %d", &tp[i], &tf[i]);

		printf("%d\n", solve());
	}

	return 0;
}
