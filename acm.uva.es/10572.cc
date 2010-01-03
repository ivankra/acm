#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <map>
using namespace std;

int nrows, ncols, has_sol;
char partial[8][8], grid[8][8], sol[8][8];

struct State {
	char color[8], up_left, comp[8], ncomp, nwhite, nblack;

	void normalize() {
		static int a[10];
		for (int i = 0; i < 9; i++) a[i] = -1;

		ncomp = 0;
		nwhite = nblack = 0;
		for (int i = 0; i < ncols; i++) {
			if (a[comp[i]] < 0) {
				a[comp[i]] = ncomp++;
				if (color[i] == 0) nwhite++; else nblack++;
			}
			comp[i] = a[comp[i]];
		}
	}

	void merge(int a, int b) {
		if (a != b) {
			for (int i = 0; i < ncols; i++)
				if (comp[i] == b) comp[i] = a;
		}
	}

	unsigned encode() {
		unsigned key = 0;
		for (int i = 0; i < ncols; i++)
			key = key * 16 + color[i] * 8 + comp[i];
		return key;
	}
};

map<unsigned, int> memo[8][8][2];

int rec(int row, int col, State S, int force_color) {
	if (col == ncols) { col = 0; row++; }
	S.normalize();

	if (row == nrows) {
		if (S.nwhite > 1 || S.nblack > 1) return 0;
		if (has_sol == 0) {
			has_sol = 1;
			for (int i = 0; i < nrows; i++)
				for (int j = 0; j < ncols; j++)
					sol[i][j] = grid[i][j];
		}
		return 1;
	}

	if (row > 0 && col > 0 && S.color[col] != S.color[col-1])
		S.up_left = 0;

	unsigned key;
	if (force_color < 0) {
		key = S.encode();
		if (memo[row][col][S.up_left].count(key) != 0)
			return memo[row][col][S.up_left][key];
	}

	int res = 0;

	// white
	do {
		if (force_color == 1) break;
		if (partial[row][col] == '#') break;
		if (row > 0 && col > 0 &&
		    S.color[col-1] == 0 && S.color[col] == 0 && S.up_left == 0)
			break;

		State T = S;
		T.color[col] = 0;
		T.up_left = S.color[col];
		T.comp[col] = (row > 0 && S.color[col] == 0) ? S.comp[col] : S.ncomp;
		if (col > 0 && T.color[col-1] == 0) T.merge(T.comp[col-1], T.comp[col]);

		grid[row][col] = 'o';

		if (row > 0 && S.color[col] == 1) {
			int m = 0;
			for (int i = 0; i < ncols; i++)
				if (T.comp[i] == S.comp[col]) { m = 1; break; }
			if (m == 0) {
				if (S.nblack > 1 || row < nrows-2) break;
				res += rec(row, col+1, T, 0);
				break;
			}
		}

		res += rec(row, col+1, T, force_color);
	} while (false);

	// black
	do {
		if (force_color == 0) break;
		if (partial[row][col] == 'o') break;
		if (row > 0 && col > 0 &&
		    S.color[col-1] == 1 && S.color[col] == 1 && S.up_left == 1)
			break;

		State T = S;
		T.color[col] = 1;
		T.up_left = S.color[col];
		T.comp[col] = (row > 0 && S.color[col] == 1) ? S.comp[col] : S.ncomp;
		if (col > 0 && T.color[col-1] == 1) T.merge(T.comp[col-1], T.comp[col]);

		grid[row][col] = '#';

		if (row > 0 && S.color[col] == 0) {
			int m = 0;
			for (int i = 0; i < ncols; i++)
				if (T.comp[i] == S.comp[col]) { m = 1; break; }
			if (m == 0) {
				if (S.nwhite > 1 || row < nrows-2) break;
				res += rec(row, col+1, T, 1);
				break;
			}
		}

		res += rec(row, col+1, T, force_color);
	} while (false);

	if (force_color < 0)
		memo[row][col][S.up_left][key] = res;
	return res;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &nrows, &ncols);

		for (int i = 0; i < nrows; i++)
			for (int j = 0; j < ncols; j++)
				scanf(" %c", &partial[i][j]);

		State S;
		memset(&S, 0, sizeof(S));

		S.normalize();

		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				for (int k = 0; k < 2; k++)
					memo[i][j][k].clear();

		has_sol = 0;
		printf("%d\n", rec(0, 0, S, -1));
		if (has_sol) {
			for (int i = 0; i < nrows; i++) {
				for (int j = 0; j < ncols; j++)
					putchar(sol[i][j]);
				putchar('\n');
			}
		}
		printf("\n");
	}

}
