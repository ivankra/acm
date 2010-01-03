#include <stdio.h>
#include <string.h>

int n1, n2, n3;
long long arr[32][32][32];
long long xyz_sum[32][32][32];
long long yz_sum[32][32][32];
long long z_sum[32][32][32];

long long solve()
{
	int i, j, k, x1, x2, y1, y2;
	long long r, s;

	scanf("%d %d %d", &n1, &n2, &n3);
	memset(arr, 0, sizeof(arr));

	for (i = 1; i <= n1; i++)
		for (j = 1; j <= n2; j++)
			for (k = 1; k <= n3; k++)
				scanf("%lld", &arr[i][j][k]);

	memset(z_sum, 0, sizeof(z_sum));
	for (i = 1; i <= n1; i++)
		for (j = 1; j <= n2; j++)
			for (z_sum[i][j][0] = 0, k = 1; k <= n3; k++)
				z_sum[i][j][k] = z_sum[i][j][k - 1] + arr[i][j][k];

	memset(yz_sum, 0, sizeof(yz_sum));
	for (i = 1; i <= n1; i++)
		for (j = 1; j <= n2; j++)
			for (k = 1; k <= n3; k++)
				yz_sum[i][j][k] = yz_sum[i][j - 1][k] + z_sum[i][j][k];

	memset(xyz_sum, 0, sizeof(xyz_sum));
	for (i = 1; i <= n1; i++)
		for (j = 1; j <= n2; j++)
			for (k = 1; k <= n2; k++)
				xyz_sum[i][j][k] = xyz_sum[i - 1][j][k] + yz_sum[i][j][k];

	for (r = arr[1][1][1], i = 1; i <= n1; i++)
		for (j = 1; j <= n2; j++)
			for (k = 1; k <= n3; k++)
				if (arr[i][j][k] > r) r = arr[i][j][k];

	for (x1 = 0; x1 < n1; x1++) {
		for (x2 = x1 + 1; x2 <= n1; x2++) {
			for (y1 = 0; y1 < n2; y1++) {
				for (y2 = y1 + 1; y2 <= n2; y2++) {
					for (s = 0, i = 1; i <= n3; i++) {

  s += xyz_sum[x2][y2][i]
     - xyz_sum[x1][y2][i] - xyz_sum[x2][y1][i] - xyz_sum[x2][y2][i - 1]
     + xyz_sum[x1][y1][i] + xyz_sum[x1][y2][i - 1] + xyz_sum[x2][y1][i - 1]
     - xyz_sum[x1][y1][i - 1];

						if (s < 0)
							s = 0;
						else if (s > r)
							r = s;
					}
				}
			}
		}
	}

	return r;
}

int main()
{
	int t;

	for (scanf("%d", &t); t-- > 0;)
		printf("%lld\n%s", solve(), t ? "\n" : "");

	return 0;
}
