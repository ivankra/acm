#include <stdio.h>
#include <string.h>

int piece[8], npiece, sol[8], board;
char out[4][4];

int solve(int k)
{
	int i, j;

	if (k >= npiece)
		return (board == 0xFFFF);

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			sol[k] = piece[k] >> (4 * i + j);

			if ((sol[k] & board) == 0) {
				board |= sol[k];
				if (solve(k + 1))
					return 1;
				board ^= sol[k];
			}

			if ((sol[k] & 0x1111) != 0) break;
		}
		if ((sol[k] & 0x000F) != 0) break;
	}

	return 0;
}

void put(int a, int c)
{
	int i, j;

	for (i = 3; i >= 0; i--)
		for (j = 3; j >= 0; j--, a >>= 1)
			if (a & 1) out[i][j] = c;
}

void readp(int p)
{
	static int d[8][8], w, h;
	int i, j, k;

	scanf("%d %d", &h, &w);
	memset(d, 0, sizeof(d));
	for (i = 0; i < h; i++)
		for (j = 0; j < w && (k = getchar()) != EOF;)
			if (k == '0' || k == '1') d[i][j++] = k - '0';

	for (k = 0, i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			k = (k << 1) | d[i][j];

	if ((piece[p] = k) == 0)
		return;

	while ((piece[p] & 0xF000) == 0)
		piece[p] <<= 4;

	while ((piece[p] & 0x8888) == 0)
		piece[p] <<= 1;
}

int main()
{
	int i, j, t;

	for (t = 0; scanf("%d", &npiece) == 1 && npiece > 0;) {
		if (t++ != 0) printf("\n");

		memset(piece, 0, sizeof(piece));
		for (i = 0; i < npiece; i++)
			readp(i);

		board = 0;
		if (solve(0) == 0) {
			printf("No solution possible\n");
			continue;
		}

		memset(out, '.', sizeof(out));

		for (i = 0; i < npiece; i++)
			put(sol[i], i + '1');

		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++)
				putchar(out[i][j]);
			putchar('\n');
		}
	}

	return 0;
}
