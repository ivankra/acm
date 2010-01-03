#include <stdio.h>
#include <string.h>

int face[24], left[24], right[24], up[24], down[24], list[24][8], nlist = 0;
int board[8][8], loc[8][8];

int get(int a[])
{
	int i, j;

	for (i = 0; i < nlist; i++) {
		for (j = 0; j < 6 && list[i][j] == a[j]; j++);
		if (j == 6) return i;
	}

	for (i = 0; i < 6; i++)
		list[nlist][i] = a[i];

	return nlist++;
}

void xrot(int a[])
{
	int t = a[0];
	a[0] = a[3];
	a[3] = a[2];
	a[2] = a[1];
	a[1] = t;
}

void yrot(int a[])
{
	int t = a[1];
	a[1] = a[5];
	a[5] = a[3];
	a[3] = a[4];
	a[4] = t;
}

void zrot(int a[])
{
	int t = a[0];
	a[0] = a[4];
	a[4] = a[2];
	a[2] = a[5];
	a[5] = t;
}

void make()
{
	int a[] = { 1, 2, 3, 4, 5, 6 };
	int i, j, k;

	for (i = 0; i < 4; i++, xrot(a))
		for (j = 0; j < 4; j++, yrot(a))
			for (k = 0; k < 4; k++, zrot(a))
				get(a);

	for (i = 0; i < 24; i++) {
		face[i] = list[i][3];

		for (j = 0; j < 6; j++)
			a[j] = list[i][j];

		xrot(a);
		up[i] = get(a);
		xrot(a);
		xrot(a);
		down[i] = get(a);
		xrot(a);

		yrot(a);
		right[i] = get(a);
		yrot(a);
		yrot(a);
		left[i] = get(a);
	}
}

int sol()
{
	int dy[] = { -1, 1, 0, 0 }, dx[] = { 0, 0, -1, 1 };
	int *dz[] = { up, down, left, right }, sy[8], sx[8], got[8];
	int i, j, t, x, y, z, x1, y1, z1;

	for (t = 0, i = 1; i <= 6; i++)
		for (j = 1; j <= 6; t += board[i][j++])
			if (board[i][j] != 0 && board[i][j] != 1) return 0;

	if (t != 6)
		return 0;

	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			loc[i][j] = -1;

	for (t = 0, i = 1; t == 0 && i <= 6; i++)
		for (j = 1; t == 0 && j <= 6; j++)
			if (board[i][j]) sy[t] = i, sx[t] = j, t++;

	memset(got, 0, sizeof(got));
	got[face[loc[sy[0]][sx[0]] = 0]] = 1;

	while (t-- > 0) {
		x = sx[t];
		y = sy[t];
		z = loc[y][x];

		for (i = 0; i < 4; i++) {
			x1 = x + dx[i];
			y1 = y + dy[i];
			z1 = dz[i][z];

			if (board[y1][x1] == 0)
				continue;

			if (loc[y1][x1] >= 0) {
				if (loc[y1][x1] != z1) return 0;
				continue;
			}

			if (got[face[z1]]++)
				return 0;

			loc[y1][x1] = z1;
			sy[t] = y1;
			sx[t] = x1;
			t++;
		}
	}

	for (i = 1; i <= 6; i++)
		if (got[i] == 0) return 0;

	return 1;
}

int main()
{
	int i, j, t;

	make();

	for (scanf("%d", &t); t-- > 0;) {
		memset(board, 0, sizeof(board));
		for (i = 1; i <= 6; i++)
			for (j = 1; j <= 6; j++)
				scanf("%d", &board[i][j]);

		printf(t ? "%s\n\n" : "%s\n", sol() ? "correct" : "incorrect");
	}

	return 0;
}
