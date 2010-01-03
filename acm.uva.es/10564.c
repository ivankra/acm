#include <stdio.h>
#include <string.h>
#include <assert.h>

int A[48][48], L[48][48], R[48][48], G[48][48][512], id, bottom, n;
long long F[48][48][512];

long long f(int r, int c, int s)
{
	if (G[r][c][s] == id) return F[r][c][s];
	G[r][c][s] = id;

	if (A[r][c] < 0 || s < 0)
		return (F[r][c][s] = 0);
	else if (r == bottom)
		return (F[r][c][s] = ((s == A[r][c]) ? 1 : 0));
	else
		return (F[r][c][s] = f(r + 1, L[r][c], s - A[r][c]) +
				     f(r + 1, R[r][c], s - A[r][c]));
}

int main()
{
	int i, j, s;
	long long t;

	/* memset(G, 0, sizeof(G)); */

	for (id = 1; scanf("%d %d", &n, &s) == 2 && n > 0; id++) {
		for (i = 0; i < 48; i++)
			for (j = 0; j < 48; j++)
				A[i][j] = -1, L[i][j] = R[i][j] = 0;

		for (i = 1; i < n; i++) {
			for (j = 1; j <= (n - i + 1); j++) {
				scanf("%d", &A[i][j]);
				L[i][j] = j - 1;
				R[i][j] = j;
			}
		}

		for (i = 1; i <= n; i++) {
			for (j = 1; j <= i; j++) {
				scanf("%d", &A[n + i - 1][j]);
				L[n + i - 1][j] = j;
				R[n + i - 1][j] = j + 1;
			}
		}

		bottom = 2 * n - 1;

		for (i = 1, t = 0; i <= n; i++)
			t += f(1, i, s);

		printf("%lld\n", t);

		if (t == 0) {
			printf("\n");
			continue;
		}

		for (j = 1; f(1, j, s) == 0; j++);
		printf("%d ", j - 1);

		for (i = 1; i < bottom; i++) {
			s -= A[i][j];
			if (f(i + 1, L[i][j], s) > 0) {
				j = L[i][j];
				putchar('L');
			} else {
				j = R[i][j];
				putchar('R');
			}
		}

		putchar('\n');
	}

	return 0;
}
