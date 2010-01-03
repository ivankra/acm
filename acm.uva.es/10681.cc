#include <cstdio>
#include <cstring>

#define INF 10000

int d[200][200], N, M;

int main() {
	while (scanf("%d %d", &N, &M) == 2 && N > 0) {
		for (int i = 0; i < 2*N; i++)
			for (int j = 0; j < 2*N; j++)
				d[i][j] = (i==j ? 0 : INF);

		for (int i = 0; i < M; i++) {
			int A, B;
			scanf("%d %d", &A, &B);
			A--; B--;
			if (A != B) {
				d[A][N+B] = d[B][N+A] = 1;
				d[N+B][A] = d[N+A][B] = 1;
			}
		}

		for (int k = 0; k < 2*N; k++)
		for (int i = 0; i < 2*N; i++)
		for (int j = 0; j < 2*N; j++)
			d[i][j] <?= d[i][k] + d[k][j];

		int S, T, D;
		scanf("%d %d %d", &S, &T, &D);
		S--; T--;

		if (d[S][(D%2)*N+T] <= D)
			printf("Yes, Teobaldo can travel.\n");
		else
			printf("No, Teobaldo can not travel.\n");
	}
}
