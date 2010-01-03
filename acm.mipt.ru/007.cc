#include <cstdio>
#include <cstring>

int a[32][32][32], sum[32][32][32], n1, n2, n3;

int main() {
	scanf("%d %d %d", &n2, &n3, &n1);

#define forall for(int i=1,j,k;i<=n1;i++) for(j=1;j<=n2;j++) for(k=1;k<=n3;k++)

	forall scanf("%d", &a[i][j][k]);

	memset(sum, 0, sizeof(sum));
	forall sum[i][j][k] = a[i][j][k];
	forall sum[i][j][k] += sum[i][j][k-1];
	forall sum[i][j][k] += sum[i][j-1][k];
	forall sum[i][j][k] += sum[i-1][j][k];

	int maxi = a[1][1][1];
	forall maxi >?= a[i][j][k];

	int best = 0;
	for (int x1 = 0; x1 < n1; x1++)
	for (int x2 = x1+1; x2 <= n1; x2++)
	for (int y1 = 0; y1 < n2; y1++)
	for (int y2 = y1+1; y2 <= n2; y2++)
	for (int z1 = 0; z1 < n3; z1++)
	for (int z2 = z1+1; z2 <= n3; z2++)
		best >?=
			+ sum[x2][y2][z2]
			- sum[x1][y2][z2] - sum[x2][y1][z2] - sum[x2][y2][z1]
			+ sum[x1][y1][z2] + sum[x1][y2][z1] + sum[x2][y1][z1]
			- sum[x1][y1][z1];
	printf("%d\n", (maxi < 0 ? maxi : best));
}
