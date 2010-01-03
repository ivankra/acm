#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int move[8192][4], nmoves;
int a[16][16];

int valid(int r, int c)
{
	return (1 <= r && r <= 8) && (1 <= c && c <= 8);
}

void add(int r1, int c1, int r2, int c2)
{
	move[nmoves][0] = r1;
	move[nmoves][1] = c1;
	move[nmoves][2] = r2;
	move[nmoves][3] = c2;
	nmoves++;
}

void go(int r, int c)
{
	int dx, dy, i, j, k;

	for (dx = -1; dx <= 1; dx++) {
		for (dy = -1; dy <= 1; dy++) {
			if (dx == 0 && dy == 0)
				continue;

			for (k = -1, i = r, j = c; valid(i, j); i += dy, j += dx)
				if (a[i][j] != 0) k++;

			for (i = r, j = c; valid(i, j); i -= dy, j -= dx)
				if (a[i][j] != 0) k++;

			if (k <= 0 || !valid(r + k * dy, c + k * dx))
				continue;

			if (a[r + k * dy][c + k * dx] == a[r][c])
				continue;

			for (i = 1; i < k; i++)
				if (a[r + i * dy][c + i * dx] != 0 &&
				    a[r + i * dy][c + i * dx] != a[r][c]) break;
			if (i < k) continue;

			add(r, c, r + k * dy, c + k * dx);
		}
	}
}

int compare(const void *p, const void *q)
{
	return memcmp(p, q, 4 * sizeof(int));
}

int main()
{
	int i, j, c, t;

	for (t = 0;;) {
		memset(a, 0, sizeof(a));
		for (i = 1; i <= 8; i++) {
			for (j = 1; j <= 8 && (c = getchar()) != EOF;)
				if (c == '.')
					a[i][j++] = 0;
				else if (c == 'X')
					a[i][j++] = 1;
				else if (c == 'O')
					a[i][j++] = 2;
			if (j <= 8) break;
		}
		if (i <= 8) break;

		if (t++ != 0) printf("\n");

		while ((c = getchar()) != EOF && c != 'X' && c != 'O');
		if (c == EOF) break;

		c = (c == 'X') ? 1 : 2;

		for (nmoves = 0, i = 1; i <= 8; i++)
			for (j = 1; j <= 8; j++)
				if (a[i][j] == c) go(i, j);

		qsort(move, nmoves, sizeof(move[0]), &compare);

		for (i = 0; i < nmoves; i++)
			printf("%c%c-%c%c\n",
				move[i][0] + 'A' - 1, move[i][1] + '0',
				move[i][2] + 'A' - 1, move[i][3] + '0');

		if (nmoves == 0)
			printf("No moves are possible\n");
	}

	return 0;
}
