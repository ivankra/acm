#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <cmath>
#include <cassert>
#include <map>
using namespace std;
typedef vector<int> VI;

char board[128][128];
int color[128][128], used[128], N, K;

void recolor(int row, int col, int kind)
{
	int i;

	color[row][col] = 0;
	memset(used, 0, sizeof(used));

	if (kind == 0) {
		for (i = 0; i < N; i++)
			used[color[row][i]] = 1;

		for (color[row][col] = 1; color[row][col] <= K; ++color[row][col])
			if (!used[color[row][col]]) break;
		assert(color[row][col] <= K);

		for (i = 0; i < N; i++) {
			if (i != row && color[i][col] == color[row][col]) {
				recolor(i, col, 1);
			}
		}

	} else {

		for (i = 0; i < N; i++)
			used[color[i][col]] = 1;

		for (color[row][col] = 1; color[row][col] <= K; ++color[row][col])
			if (!used[color[row][col]]) break;
		assert(color[row][col] <= K);

		for (i = 0; i < N; i++) {
			if (i != col && color[row][i] == color[row][col]) {
				recolor(row, i, 0);
			}
		}
	}
}

int main()
{
	int i, j, T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		for (i = 0; i < N; i++)
			for (j = 0; j < N; j++)
				scanf(" %c", &board[i][j]);

		K = 0;
		for (i = 0; i < N; i++) {
			int c1 = 0, c2 = 0;
			for (j = 0; j < N; j++) {
				c1 += board[i][j] == '*';
				c2 += board[j][i] == '*';
			}
			K = max(K, max(c1, c2));
		}

		memset(color, 0, sizeof(color));
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				if (board[i][j] == '*' && color[i][j] == 0)
					recolor(i, j, 0);
			}
		}

		printf("%d\n", K);
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) printf(j == 0 ? "%d" : " %d", color[i][j]);
			printf("\n");
		}

	}
}
