#include <cstdio>
#include <cstring>

int main()
{
	int n, a[16][16], sum[16][16];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &a[i][j]);

	memset(sum, 0, sizeof(sum));
	for (int i = 1; i <= n; i++) {
		int t = 0;
		for (int j = 1; j <= n; j++) {
			t += a[i-1][j-1];
			sum[i][j] = sum[i-1][j] + t;
		}
	}

	int best = 0;
	for (int r0 = 0; r0 < n; r0++)
	for (int r1 = r0; r1 < n; r1++)
	for (int c0 = 0; c0 < n; c0++)
	for (int c1 = c0; c1 < n; c1++)
		best>?=sum[r1+1][c1+1]-sum[r1+1][c0]-sum[r0][c1+1]+sum[r0][c0];

	printf("%d\n", best);			
}
