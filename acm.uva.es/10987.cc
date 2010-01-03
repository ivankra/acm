#include <stdio.h>

int a[128][128], d[128][128], n, m;

int solve()
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (d[i][k]+d[k][j] < d[i][j])
					return 1;

	m = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			a[i][j] = a[j][i] = 1;
			for (int k = 0; k < n; k++)
				if (k != i && k != j && d[i][k] + d[k][j] == d[i][j])
					a[i][j] = a[j][i] = 0;
			m += a[i][j];
		}
	}

	printf("%d\n", m);
	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			if (a[i][j]) printf("%d %d %d\n", i+1, j+1, d[i][j]);

	return 0;
}

int main()
{
	int T, cs = 1;
	for (scanf("%d", &T); cs <= T && scanf("%d", &n); cs++) {
		printf("Case #%d:\n", cs);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i; j++) {
				scanf("%d", &d[i][j]);
				d[j][i] = d[i][j];
			}
			d[i][i] = 0;
		}
		if (solve()) printf("Need better measurements.\n");
		printf("\n");
	}
	return 0;
}
