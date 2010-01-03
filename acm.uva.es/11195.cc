#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int N, next[16], prev[16], res;
char board[16][16];

void rec(int row, int diag1, int diag2) {
	for (int col = next[0]; col != 0; col = next[col]) {
		if (board[row][col] != '.') continue;
		if ((diag1 >> (row + col)) & 1) continue;
		if ((diag2 >> (row - col + 15)) & 1) continue;

		if (row == N) {
			res++;
		} else {
			next[prev[col]] = next[col];
			prev[next[col]] = prev[col];

			rec(
				row+1,
				diag1 | (1 << (row + col)),
				diag2 | (1 << (row - col + 15))
			);

			next[prev[col]] = col;
			prev[next[col]] = col;
		}
	}

}

int main() {
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				scanf(" %c", &board[i][j]);

		for (int i = 0; i < 16; i++) { next[i] = i + 1; prev[i] = i - 1; }
		next[N] = 0; prev[0] = N;
		res = 0;

		rec(1, 0, 0);

		printf("Case %d: %d\n", cs, res);
	}
}
