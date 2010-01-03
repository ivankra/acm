#include <stdio.h>
#include <string.h>

int main()
{
	static __int64 a[16][16][16];
	int i, k, r, c, n, m;

	scanf("%d %d", &n, &m);

	if (m > n) {
		printf("0\n");
		return 0;
	}

	memset(a, 0, sizeof(a));
	for (r = 0; r <= n; r++) for (c = 0; c <= n; c++) a[r][c][0] = 1;

	for (r = 1; r <= n; r++)
		for (c = 1; c <= n; c++)
			for (k = 1; k <= r && k <= c; k++)
				for (i = 0; i < r; i++)
					a[r][c][k] += a[i][c-1][k-1] * c;

	printf("%I64d\n", a[n][n][m]);
	return 0;
}
