#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LEFT	1
#define RIGHT	2
#define TOP	4
#define BOTTOM	8

char board[128][128];
int state[128][128], n;

int neighbors(int y, int x)
{
	int r;

	r = (y > 0) ? state[y - 1][x] : TOP;
	r |= (y < (n - 1)) ? state[y + 1][x] : BOTTOM;
	r |= (x > 0) ? state[y][x - 1] : LEFT;
	r |= (x < (n - 1)) ? state[y][x + 1] : RIGHT;

	return r;
}

void dfs(int y, int x, int c)
{
	static int sy[32768], sx[32768];
	int p;

	for (state[y][x] |= c, sy[0] = y, sx[0] = x, p = 1; p > 0;) {
		p--;
		y = sy[p];
		x = sx[p];

#define GO(NY,NX) if (0<=(NY) && (NY)<n && 0<=(NX) && (NX)<n && \
		    board[NY][NX] == board[y][x] && !(state[NY][NX] & c)) \
			{ sy[p] = NY; sx[p] = NX; p++; state[NY][NX] |= c; }
		GO(y - 1, x);
		GO(y + 1, x);
		GO(y, x - 1);
		GO(y, x + 1);
#undef GO
	}
}

char *solve()
{
	int i, j;

	memset(state, 0, sizeof(state));

	for (i = 0; i < n; i++)
		if (board[i][0] == 'W') dfs(i, 0, LEFT);

	for (i = 0; i < n; i++)
		if (board[i][n - 1] == 'W') dfs(i, n - 1, RIGHT);

	for (i = 0; i < n; i++)
		if (board[0][i] == 'B') dfs(0, i, TOP);

	for (i = 0; i < n; i++)
		if (board[n - 1][i] == 'B') dfs(n - 1, i, BOTTOM);

	for (i = 0; i < n; i++)
		if ((state[i][0] & (LEFT | RIGHT)) == (LEFT | RIGHT))
			return "White has a winning path.";

	for (i = 0; i < n; i++)
		if ((state[0][i] & (TOP | BOTTOM)) == (TOP | BOTTOM))
			return "Black has a winning path.";

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (board[i][j] == 'U' &&
			    (neighbors(i, j) & (LEFT | RIGHT)) == (LEFT | RIGHT))
				return "White can win in one move.";

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (board[i][j] == 'U' &&
			    (neighbors(i, j) & (TOP | BOTTOM)) == (TOP | BOTTOM))
				return "Black can win in one move.";

	return "There is no winning path.";
}

int main()
{
	int i, j, c;

	while (scanf("%d", &n) == 1 && n > 0) {
		memset(board, 0, sizeof(board));

		for (i = 0; i < n; i++)
			for (j = 0; j < n && (c = getchar()) != EOF;)
				if (isalpha(c)) board[i][j++] = toupper(c);

		printf("%s\n", solve());
	}

	return 0;
}
