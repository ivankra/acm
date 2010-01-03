#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;

int N, score[2], seen1[32][32], seen2[32][32], seen3[32][32];
char board[32][32];

bool dfs1(int y, int x, char border) {
	if (y < 1 || y > N || x < 1 || x > N || board[y][x] == border) return false;
	if (board[y][x] == ' ') return true;
	if (seen1[y][x]) return false;
	seen1[y][x] = 1;

	bool res = false;
	for (int dy = -1; dy <= 1; dy++) {
		for (int dx = -1; dx <= 1; dx++) {
			if (dy*dx != 0) continue;
			res |= dfs1(y+dy, x+dx, border);
		}
	}
	return res;
}

int dfs2(int y, int x, char border) {
	if (y < 1 || y > N || x < 1 || x > N || board[y][x] == border) return 0;
	if (seen2[y][x]) return 0;
	seen2[y][x] = 1;

	int res = 0;
	if (board[y][x] != ' ') {
		board[y][x] = ' ';
		res++;
	}

	for (int dy = -1; dy <= 1; dy++) {
		for (int dx = -1; dx <= 1; dx++) {
			if (dy*dx != 0) continue;
			res += dfs2(y+dy, x+dx, border);
		}
	}
	return res;
}

void do_captures(char color) {
	char opposite = (color == 'B' ? 'W' : 'B');

	memset(seen1, 0, sizeof(seen1));
	memset(seen2, 0, sizeof(seen2));
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			if (!seen1[y][x] && board[y][x] == opposite && !dfs1(y, x, color)) {
				score[color == 'B' ? 0 : 1] += dfs2(y, x, color);
			}
		}
	}
}

int dfs3(int y, int x, char border) {
	if (y < 1 || y > N || x < 1 || x > N) return 0;
	if (board[y][x] == border || seen3[y][x]) return 0;
	if (board[y][x] != ' ') return -1;
	seen3[y][x] = 1;

	int res = 1;
	for (int dy = -1; dy <= 1; dy++) {	
		for (int dx = -1; dx <= 1; dx++) {
			if (dy*dx != 0) continue;
			int t = dfs3(y+dy, x+dx, border);
			if (t < 0) res = -1; else if (res > 0) res += t;
		}
	}
	return res;
}

void do_owned(char color) {
	memset(seen3, 0, sizeof(seen3));
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			if (seen3[y][x] || board[y][x] != ' ') continue;
			int t = dfs3(y, x, color);
			score[color == 'B' ? 0 : 1] += max(0, t);
		}
	}
}

int main() {
	int M;
	while (scanf("%d %d", &N, &M) == 2 && N > 0) {
		memset(board, ' ', sizeof(board));
		score[0] = score[1] = 0;

		for (int i = 0; i < M; i++) {
			char color;
			int x, y;
			scanf(" %c ( %d , %d )", &color, &x, &y);
			x += (N-1)/2 + 1;
			y += (N-1)/2 + 1;

/*			printf("board:\n");
			{for (int y = 1; y <= N; y++) {
				for (int x = 1; x <= N; x++) putchar(board[y][x]==' '?'.':board[y][x]);
				printf("\n");}}
			printf("\n%c y=%d x=%d\n", color, y, x);
*/
			assert(board[y][x] == ' ');
			board[y][x] = color;

			do_captures(color);
		}

		do_owned('B');
		do_owned('W');

		printf("%d %d\n", score[0], score[1]);
	}
}
