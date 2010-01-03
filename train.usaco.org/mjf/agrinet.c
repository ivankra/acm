/*
ID: mjf28791
PROG: agrinet
LANG: C
*/
#include <stdio.h>

int d[128][128], u[128], n;

int main()
{
	int i, j, k, r;

	freopen("agrinet.in", "r", stdin);
	freopen("agrinet.out", "w", stdout);

	scanf("%d", &n);

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &d[i][j]);

	for (i = 0; i < n; i++)
		u[i] = d[0][i];
	u[0] = -1;

	for (r = 0;;) {
		for (k = 0; k < n && u[k] < 0; k++);
		if (k == n) break;

		for (i = k + 1; i < n; i++)
			if (u[i] >= 0 && u[i] < u[k]) k = i;

		r += u[k];

		for (i = 0; i < n; i++)
			if (u[i] >= 0 && d[k][i] < u[i]) u[i] = d[k][i];
		u[k] = -1;
	}

	printf("%d\n", r);
	return 0;
}
