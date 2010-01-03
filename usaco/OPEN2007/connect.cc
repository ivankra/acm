/*
ID: infnty1
LANG: C++
TASK: connect
*/
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;

enum { JUMP = 122 };

int vroad[16384];	// vroad[c] = is there a road between (1,c) and (2,c)
int hroad[2][16384];	// hroad[r][c] = is there a road between (r,c) and (r,c+1)

// jump[r1][r2][c] = is it possible to move from (r1,c) to (r2,c+JUMP) using only up, down and right moves
int jump[2][2][16384];

void dump() {
	printf("\nJUMP=%d\n", JUMP);
	for (int col = 1; col < 10; col++)
		printf("%d%d%c", jump[0][0][col], jump[0][1][col], hroad[0][col] ? '-' : ' ');
	printf("\n");
	for (int col = 1; col < 10; col++)
		printf("%c  ", vroad[col] ? '|' : ' ');
	printf("\n");
	for (int col = 1; col < 10; col++)
		printf("%d%d%c", jump[1][0][col], jump[1][1][col], hroad[1][col] ? '-' : ' ');
	printf("\n\n");
}

void readMap()
{
	memset(vroad, 0, sizeof(vroad));
	memset(hroad, 0, sizeof(hroad));

	int N;
	FILE *fp = fopen("connect.in", "r");
	fscanf(fp, "%d", &N);

	for (int i = 0; i < N; i++) {
		int r1, c1, r2, c2;
		fscanf(fp, "%d %d %d %d", &r1, &c1, &r2, &c2); r1--; r2--;
		assert(c1 == c2 || r1 == r2);

		if (c1 == c2) {
			assert((r1 == 0 && r2 == 1) || (r1 == 1 && r2 == 0));
			vroad[c1] = 1;
		} else {
			assert(c1 == c2 + 1 || c2 == c1 + 1);
			hroad[r1][min(c1, c2)] = 1;
		}
	}

	fclose(fp);
}

void computeJump()
{
	static int a[2][16384];
	memset(jump, 0, sizeof(jump));
	for (int col = 0; col <= 15010; col++) {
		for (int row = 0; row < 2; row++) {
			a[row][col] = 1;
			a[1-row][col] = vroad[col];

			a[0][col+JUMP] = 0;
			a[1][col+JUMP] = 0;

			for (int c = col+1; c <= col+JUMP; c++) {
				a[0][c] = hroad[0][c-1] & a[0][c-1];
				a[1][c] = hroad[1][c-1] & a[1][c-1];
				if ((a[0][c] | a[1][c]) == 0) break;
				if (vroad[c])
					a[0][c] = a[1][c] = 1;
			}

			jump[row][0][col] = a[0][col+JUMP];
			jump[row][1][col] = a[1][col+JUMP];
		}
	}
}

void updateJump(int column)
{
	static int a[2][16384];

	for (int col = max(0, column-JUMP-3); col <= column+JUMP+3; col++)
		a[0][col] = a[1][col] = 0;

	int mask_left = 0;
	for (int i = 0; i < 4; i++) {
		int row = i / 2, col = column + i % 2;
		a[row][col] |= 1 << i;
		if (col == column) mask_left |= 1 << i;
	}

	for (int col = column; col <= column+1; col++) {
		if (vroad[col]) {
			a[0][col] |= a[1][col];
			a[1][col] |= a[0][col];
		}
	}

	for (int c = column; c >= 0 && c >= column-JUMP-3; c--) {
		if (hroad[0][c]) a[0][c] |= a[0][c+1];
		if (hroad[1][c]) a[1][c] |= a[1][c+1];
		if (vroad[c]) { a[0][c] |= a[1][c]; a[1][c] |= a[0][c]; }
	}

	for (int c = column; c <= column+JUMP+3; c++) {
		if (vroad[c]) { a[0][c] |= a[1][c]; a[1][c] |= a[0][c]; }
		if (hroad[0][c]) a[0][c+1] |= a[0][c];
		if (hroad[1][c]) a[1][c+1] |= a[1][c];
	}

	for (int col = max(0, column-JUMP); col <= column; col++) {
		for (int r1 = 0; r1 < 2; r1++) {
			for (int r2 = 0; r2 < 2; r2++) {
				int mask = a[r1][col] & a[r2][col+JUMP];
				if (col+JUMP == column) mask &= mask_left;
				jump[r1][r2][col] = (mask != 0);
			}
		}
	}
}

int query(int start_row, int start_col, int end_row, int end_col)
{
	static int a[2][16384];

	if (start_col == end_col) return vroad[start_col];
	assert(start_col < end_col);

	for (int c = start_col; c <= end_col; c += JUMP) a[0][c] = a[1][c] = 0;
	for (int c = max(0, end_col-JUMP-10); c <= end_col; c++) a[0][c] = a[1][c] = 0;

	a[start_row][start_col] = 1;
	a[1-start_row][start_col] = vroad[start_col];

	int col;

	for (col = start_col; col+JUMP <= end_col; col += JUMP) {
		if (vroad[col]) {
			a[0][col] |= a[1][col];
			a[1][col] |= a[0][col];
		}

		if ((a[0][col] | a[1][col]) == 0)
			return 0;

		for (int r1 = 0; r1 < 2; r1++)
			for (int r2 = 0; r2 < 2; r2++)
				a[r2][col+JUMP] |= jump[r1][r2][col] & a[r1][col];
	}

	for (;; col++) {
		if (vroad[col]) {
			a[0][col] |= a[1][col];
			a[1][col] |= a[0][col];
		}

		if (col == end_col)
			return a[end_row][col];

		a[0][col+1] |= a[0][col] & hroad[0][col];
		a[1][col+1] |= a[1][col] & hroad[1][col];
	}
}

int main()
{
	readMap();
	computeJump();

	setlinebuf(stdout);

	char line[1024];
	while (fgets(line, sizeof(line), stdin) && line[0] != 'E') {
		char type;
		int r1, c1, r2, c2;

		int t = sscanf(line, " %c %d %d %d %d", &type, &r1, &c1, &r2, &c2);
		assert(t == 5);

		type = toupper(type);
		if (type == '0') type = 'O';
		assert(type == 'C' || type == 'O' || type == 'T');

		r1--; r2--;

		if (c1 > c2) { swap(c1, c2); swap(r1, r2); }
		if (c1 == c2 && r1 > r2) swap(r1, r2);

		if (type == 'C') {
			if (c1 == c2) {
				vroad[c1] = 0;
			} else {
				assert(c2 == c1+1 && r1 == r2);
				hroad[r1][c1] = 0;
			}
			updateJump(c1);
		} else if (type == 'O') {
			if (c1 == c2) {
				assert(r1 == 0 && r2 == 1);
				vroad[c1] = 1;
			} else {
				assert(c2 == c1+1 && r1 == r2);
				hroad[r1][c1] = 1;
			}
			updateJump(c1);
		} else {
			if (query(r1, c1, r2, c2))
				printf("Y\n");
			else
				printf("N\n");
			fflush(stdout);
		}
	}

	return 0;
}
