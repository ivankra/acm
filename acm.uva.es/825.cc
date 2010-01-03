#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#define MAX 128

char block[MAX][MAX];
long long ways[MAX];

int main() {
	int T, nrows, ncols;
	scanf("%d", &T);

	while (T-- > 0 && scanf("%d %d", &nrows, &ncols) == 2) {
		assert(1 <= nrows && nrows < MAX);
		assert(1 <= ncols && ncols < MAX);

		memset(block, 0, sizeof(block));
		for (int i = 0; i < nrows; i++) {
			int row, col;
			scanf("%d", &row);
			for (;;) {
				int c = getchar();
				if (c == EOF || c == '\n') break;
				if (!isdigit(c)) continue;
				ungetc(c, stdin);
				scanf("%d", &col);
				block[row-1][col-1] = 1;
			}
		}

		memset(ways, 0, sizeof(ways));
		ways[0] = 1;

		for (int r = 0; r < nrows; r++)
			for (int c = 0; c < ncols; c++)
				if (block[r][c])
					ways[c] = 0;
				else
					ways[c] += (c>0 ? ways[c-1] : 0);
		printf("%lld\n", ways[ncols-1]);
		if (T) printf("\n");
	}

}
