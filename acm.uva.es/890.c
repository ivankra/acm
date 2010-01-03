#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int N[64][64], W[64][64], V[64][64], sx[8192], sy[8192], m, n, k, x, t;

int main()
{
	int i, j, c;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &m, &n) == 2;) {
		memset(N, 0, sizeof(N));
		memset(W, 0, sizeof(W));
		memset(V, 0, sizeof(V));

		scanf("%d %d", &sy[1], &sx[1]);
		V[sy[1] = m - sy[1] + 1][sx[1]] = 1;

		for (i = 0; i <= (m + 1); i++)
			V[i][0] = V[i][n + 1] = 1;

		for (i = 0; i <= (n + 1); i++)
			V[0][i] = V[m + 1][i] = 1;

		for (k = 1; k > 0;) {
			i = sy[k], j = sx[k];
			if (V[i-1][j] & V[i+1][j] & V[i][j-1] & V[i][j+1]) {
				k--;
				continue;
			}

			while ((c = getchar()) != EOF && !isalpha(c));
			assert(c != EOF);

			if (c == 'F') {
				scanf("%d", &x);
				for (i = x, j = k; i < j; i++, j--)
					c = sx[i], sx[i] = sx[j], sx[j] = c,
					c = sy[i], sy[i] = sy[j], sy[j] = c;
				continue;
			}

			if (c == 'U')
				N[i][j] = 1, k++, sy[k] = i - 1, sx[k] = j;
			else if (c == 'D')
				N[i+1][j] = 1, k++, sy[k] = i + 1, sx[k] = j;
			else if (c == 'L')
				W[i][j] = 1, k++, sy[k] = i, sx[k] = j - 1;
			else
				W[i][j+1] = 1, k++, sy[k] = i, sx[k] = j + 1;

			V[sy[k]][sx[k]] = 1;
		}

		for (i = 0; i < n; i++)
			printf(" _");
		printf("\n");
		for (i = 1; i <= m; i++) {
			for (j = 1; j <= n; j++) {
				putchar(W[i][j] ? ' ' : '|');
				putchar(N[i+1][j] ? ' ' : '_');
			}
			printf("|\n");
		}
		printf("\n");
	}

	return 0;
}
