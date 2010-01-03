#include <cstdio>

int N, K;
int a[128][128];

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &N, &K);
		for (int i = 0; i < N; i++) scanf("%d", &a[0][i]);

		for (int k = 1; k < N; k++)
			for (int i = 0; i < N-k; i++)
				a[k][i] = a[k-1][i+1] - a[k-1][i];

		for (int s = N; s < N+K; s++) {
			a[s][0] = 0;
			for (int k = s-1; k >= 0; k--)
				a[k][s-k] = a[k][s-k-1] + a[k+1][s-k-1];
			printf("%d ", a[0][s]);
		}
		printf("\n");
	}
}
