#include <stdio.h>
#include <string.h>

int n1, n2, n3;
long long arr[32][32][32];
long long arr2[32][32];

static long long plane()
{
	static long long sum[32][32], r, s;
	int i, j, k;

	memset(sum, 0, sizeof(sum));
	for (i = 1; i <= n2; i++)
		for (j = 1; j <= n3; j++)
			sum[i][j] = sum[i - 1][j] + arr2[i][j];

	r = arr2[1][1];

	for (i = 0; i < n2; i++) {
		for (j = i + 1; j <= n2; j++) {
			for (s = 0, k = 1; k <= n3; k++) {
				s += sum[j][k] - sum[i][k];

				if (s < 0)
					s = 0;
				else if (s > r)
					r = s;
			}
		}
	}

	return r;
}

long long solve()
{
	static long long x_sum[32][32][32], r, s;
	int i, j, k, x1, x2;

	scanf("%d %d %d", &n1, &n2, &n3);
	memset(arr, 0, sizeof(arr));

	for (i = 1; i <= n1; i++)
		for (j = 1; j <= n2; j++)
			for (k = 1; k <= n3; k++)
				scanf("%lld", &arr[i][j][k]);

	for (r = arr[1][1][1], i = 1; i <= n1; i++)
		for (j = 1; j <= n2; j++)
			for (k = 1; k <= n3; k++)
				if (arr[i][j][k] > r) r = arr[i][j][k];

	memset(x_sum, 0, sizeof(x_sum));
	for (i = 1; i <= n1; i++)
		for (j = 1; j <= n2; j++)
			for (k = 1; k <= n3; k++)
				x_sum[i][j][k] = x_sum[i - 1][j][k] + arr[i][j][k];

	for (x1 = 0; x1 < n1; x1++) {
		for (x2 = x1 + 1; x2 <= n1; x2++) {
			for (i = 1; i <= n2; i++)
				for (j = 1; j <= n3; j++)
					arr2[i][j] = x_sum[x2][i][j] - x_sum[x1][i][j];

			s = plane();
			if (s > r) r = s;
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
