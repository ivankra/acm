#include <stdio.h>
#include <string.h>
#include <ctype.h>

int piece[16][16], board[16][16], color[16][16];

int valid(int r, int c)
{
	return (1 <= r && r <= 8 && 1 <= c && c <= 8);
}

int atk(int r, int c, int clr)
{
	return (valid(r, c) && piece[r][c] == 'k' && color[r][c] == (clr ^ 1));
}

int ray(int r, int c, int dr, int dc, int clr)
{
	for (;;) {
		r += dr;
		c += dc;

		if (!valid(r, c))
			return 0;
		else if (piece[r][c] != 0)
			return atk(r, c, clr);
	}
}

int check(int clr)
{
	int r, c;

#define ATK(R,C) if (atk(R, C, clr)) return 1;
#define RAY(DR,DC) if (ray(r, c, DR, DC, clr)) return 1;

	/* pawns */
	if (clr == 1) {
		for (r = 1; r <= 7; r++) {
			for (c = 1; c <= 8; c++) {
				if (board[r][c] == 'p') {
					ATK(r + 1, c - 1);
					ATK(r + 1, c + 1);
				}
			}
		}
	} else {
		for (r = 2; r <= 8; r++) {
			for (c = 1; c <= 8; c++) {
				if (board[r][c] == 'P') {
					ATK(r - 1, c - 1);
					ATK(r - 1, c + 1);
				}
			}
		}
	}

	/* rooks */
	for (r = 1; r <= 8; r++) {
		for (c = 1; c <= 8; c++) {
			if (piece[r][c] == 'r' && color[r][c] == clr) {
				RAY(1, 0); RAY(-1, 0); RAY(0, 1); RAY(0, -1);
			}
		}
	}

	/* bishops */
	for (r = 1; r <= 8; r++) {
		for (c = 1; c <= 8; c++) {
			if (piece[r][c] == 'b' && color[r][c] == clr) {
				RAY(1, 1); RAY(1, -1); RAY(-1, 1); RAY(-1, -1);
			}
		}
	}

	/* queens */
	for (r = 1; r <= 8; r++) {
		for (c = 1; c <= 8; c++) {
			if (piece[r][c] == 'q' && color[r][c] == clr) {
				RAY(1, 0); RAY(-1, 0); RAY(0, 1); RAY(0, -1);
				RAY(1, 1); RAY(1, -1); RAY(-1, 1); RAY(-1, -1);
			}
		}
	}

	/* knights */
	for (r = 1; r <= 8; r++) {
		for (c = 1; c <= 8; c++) {
			if (piece[r][c] == 'n' && color[r][c] == clr) {
				ATK(r - 2, c + 1); ATK(r - 2, c - 1);
				ATK(r - 1, c + 2); ATK(r - 1, c - 2);
				ATK(r + 1, c + 2); ATK(r + 1, c - 2);
				ATK(r + 2, c + 1); ATK(r + 2, c - 1);
			}
		}
	}

#undef ATK
#undef RAY

	return 0;
}

int main()
{
	int p, i, j, c;

	for (p = 1;; p++) {
		memset(piece, 0, sizeof(piece));
		memset(board, 0, sizeof(board));
		memset(color, 0, sizeof(color));

		for (i = 1; i <= 8; i++)
			for (j = 1; j <= 8 && (c = getchar()) != EOF;)
				if (isalpha(c) || c == '.')
					board[i][j++] = c;

		for (i = 1, c = 0; i <= 8; i++) {
			for (j = 1; j <= 8; j++) {
				if (board[i][j] == '.') {
					piece[i][j] = 0;
				} else if (islower(board[i][j])) {
					piece[i][j] = board[i][j];
					color[i][j] = 1;
					c++;
				} else {
					piece[i][j] = tolower(board[i][j]);
					color[i][j] = 0;
					c++;
				}
			}
		}

		if (c == 0)
			break;

		if (check(0))
			printf("Game #%d: black king is in check.\n", p);
		else if (check(1))
			printf("Game #%d: white king is in check.\n", p);
		else
			printf("Game #%d: no king is in check.\n", p);
	}

	return 0;
}
