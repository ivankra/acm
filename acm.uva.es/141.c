#include <stdio.h>
#include <string.h>

struct {
	unsigned a[128];
} pat[1024];

int n, npat;

void rot(int a[64][64])
{
	static int t[64][64];
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			t[i][j] = a[j][n - 1 - i];

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			a[i][j] = t[i][j];

}

int add(int a[64][64])
{
	static unsigned t[128];
	int i, j, k;

	for (k = 0; k < 4; k++, rot(a)) {
		memset(t, 0, sizeof(t));

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (a[i][j] != 0)
					t[(i * n + j) >> 5] |= 1U << ((i * n + j) & 31);

		if (k == 0 || memcmp(pat[npat].a, t, 128 * sizeof(unsigned)) < 0)
			memcpy(pat[npat].a, t, 128 * sizeof(unsigned));
	}

	for (i = 0; i < npat; i++)
		if (memcmp(pat[i].a, pat[npat].a, 128 * sizeof(unsigned)) == 0)
			return 1;

	npat++;
	return 0;
}

int main()
{
	static int mx[128], my[128], board[64][64];
	static char mc[128][8];
	int i;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < (2 * n); i++)
			scanf("%d %d %s", &mx[i], &my[i], mc[i]);

		npat = 0;
		memset(board, 0, sizeof(board));

		for (i = 0; i < (2 * n); i++) {
			if (mc[i][0] == '+')
				board[my[i] - 1][mx[i] - 1] = 1;
			else
				board[my[i] - 1][mx[i] - 1] = 0;

			if (add(board))
				break;
		}

		if (i < (2 * n))
			printf("Player %d wins on move %d\n", 2 - (i & 1), i + 1);
		else
			printf("Draw\n");
	}

	return 0;
}
