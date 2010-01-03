#include <stdio.h>
#include <ctype.h>

int eq(int s, int a, int b, int c)
{
	return (a == b && b == c) ? s : 0;
}

int main()
{
	static int a[3][1024], n[3], t;
	int i, j, k, s;

	for (scanf("%d", &t); t-- > 0 && scanf("%d%d%d", &n[0], &n[1], &n[2]) == 3;) {
		for (i = 0; i < 3; i++)
			for (j = 0; j < n[i] && (k = getchar()) != EOF;)
				if (isalpha(k))
					a[i][j] = a[i][n[i] + j] = k, j++;

		for (s = 0, i = 1; i <= n[0]; i++) {
			for (j = 1; j <= n[1]; j++) {
				for (k = 1; k <= n[2]; k++) {
					s += eq(10, a[0][i], a[1][j], a[2][k]);
					s += eq(5, a[0][i-1], a[1][j-1], a[2][k-1]);
					s += eq(5, a[0][i+1], a[1][j+1], a[2][k+1]);
					s += eq(7, a[0][i-1], a[1][j], a[2][k+1]);
					s += eq(7, a[0][i+1], a[1][j], a[2][k-1]);
				}
			}
		}

		printf("%.4f\n", s / (double)(n[0] * n[1] * n[2]));
	}

	return 0;
}
