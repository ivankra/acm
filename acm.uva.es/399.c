#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int top[128], left[128], right[128], bottom[128], use[128], board[16][16];
int n, pw, ph, np;
char image[128][32][32];

int solve(int y, int x)
{
	int p;

	if (x >= n) {
		y++;
		x = 0;
	}

	if (y >= n)
		return 1;

	for (p = 0; p < np; p++) {
		if (use[p]) continue;

		if (y == 0 && top[p] != 0)
			continue;
		else if (y > 0 && (bottom[board[y - 1][x]] + top[p]) != 0)
			continue;

		if ((y + 1) >= n && bottom[p] != 0)
			continue;

		if (x == 0 && left[p] != 0)
			continue;
		else if (x > 0 && (right[board[y][x - 1]] + left[p]) != 0)
			continue;

		if ((x + 1) >= n && right[p] != 0)
			continue;

		board[y][x] = p;
		use[p] = 1;

		if (solve(y, x + 1))
			return 1;

		use[p] = 0;
	}

	return 0;
}

void rd(int p)
{
	int i, j, c;

	for (i = 0; i < ph; i++)
		for (j = 0; j < pw && (c = getchar()) != EOF;)
			if (c != '\n') image[p][i][j++] = c;

	for (i = 0; i < ph; i++)
		image[p][i][pw] = '\0';

	scanf("%d %d %d %d", &top[p], &left[p], &bottom[p], &right[p]);
}

int main()
{
	int i, j, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d %d", &n, &ph, &pw) == 3;) {
		memset(image, ' ', sizeof(image));

		np = n * n;
		for (i = 0; i < np; i++)
			rd(i);

		memset(board, 0, sizeof(board));
		memset(use, 0, sizeof(use));

		if (solve(0, 0) == 0) {
			for(;;)malloc(1000000);
		}

		for (i = 0; i < (n * ph); i++) {
			for (j = 0; j < n; j++)
				printf("%s", image[board[i / ph][j]][i % ph]);
			printf("\n");
		}

		if (t > 0)
			printf("\n");
	}

	return 0;
}
