/* O(nm) time and space */
#include <stdio.h>

#define N 1024

int A[N][N], U[N][N], L[N][N], R[N][N], LX[N][N], RX[N][N], n, m;

/* Computes the size of the largest rectangular submatrix, composed of 1's.
   A[1..n][1..m] = the input matrix, composed of 0's and 1's.
   U[i][j] = number of 1's at and above the cell A[i][j],
   L[i][j],R[i][j] = number of 1's at and to the left/right of cell A[i][j]

   LX[i][j] = how much it's possible to move left from A[i][j], such that
              U[i][...] will be >= U[i][j].
   RX[i][j] = ............................. (right) ...
   if A[i][j]=0, then LX[i][j]=RX[i][j]=0.
 */

int min(int x, int y) { return (x < y) ? x : y; }
int max(int x, int y) { return (x > y) ? x : y; }

int solve()
{
	int i, j, k;

	for (i = 1; i <= m; i++) U[0][i] = 0;

	for (i = 1; i <= n; i++) {
		L[i][0] = R[i][m+1] = 0;
		for (j = 1; j <= m; j++) {
			if (A[i][j]) {
				U[i][j] = U[i-1][j] + 1;
				L[i][j] = L[i][j-1] + 1;
			} else {
				U[i][j] = L[i][j] = 0;
			}
		}

		for (j = m; j >= 1; j--)
			R[i][j] = A[i][j] ? (R[i][j+1] + 1) : 0;
	}

	for (i = 1; i <= m; i++) {
		LX[1][i] = L[1][i];
		RX[1][i] = R[1][i];
	}

	for (i = 2; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			if (A[i-1][j] == 0) {
				LX[i][j] = L[i][j];
				RX[i][j] = R[i][j];
			} else {
				LX[i][j] = min(LX[i-1][j], L[i][j]);
				RX[i][j] = min(RX[i-1][j], R[i][j]);
			}
		}
	}

#if 0
printf("U\n");for(i=1;i<=n;i++){for(j=1;j<=m;j++)printf("%d",U[i][j]);printf("\n");}printf("\n");
printf("L\n");for(i=1;i<=n;i++){for(j=1;j<=m;j++)printf("%d",L[i][j]);printf("\n");}printf("\n");
printf("R\n");for(i=1;i<=n;i++){for(j=1;j<=m;j++)printf("%d",R[i][j]);printf("\n");}printf("\n");
printf("LX\n");for(i=1;i<=n;i++){for(j=1;j<=m;j++)printf("%d",LX[i][j]);printf("\n");}printf("\n");
printf("RX\n");for(i=1;i<=n;i++){for(j=1;j<=m;j++)printf("%d",RX[i][j]);printf("\n");}printf("\n");
#endif

	for (k = 0, i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			k = max(k, U[i][j] * (RX[i][j] + LX[i][j] - 1));

	return k;
}

int main()
{
	int i, j, k, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= m; j++) {
				while ((k = getchar()) != EOF && k != 'R' && k != 'F');
				A[i][j] = (k == 'F') ? 1 : 0;
			}
		}
		printf("%d\n", 3*solve());
	}

	return 0;
}
