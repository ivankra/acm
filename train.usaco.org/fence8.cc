/*
ID: infnty1
PROB: fence8
LANG: C++
*/
#include <cstdio>
#include <algorithm>
using namespace std;
typedef unsigned long long u64;

int board[64], N, K, board_sum[64];
int rail[1024], railused[1024], R, railleft;

static int tryit(int b, int bleft) {
	if (b == N) return 1;
	if (board_sum[N] - board_sum[b+1] + bleft < railleft) return 0;

	for (int p = K-1; p >= 0; p--) {
		if (railused[p] || rail[p] > bleft) continue;
		railused[p] = 1;
		railleft -= rail[p];
		if (tryit(b, bleft-rail[p])) return 1;
		railleft += rail[p];
		railused[p] = 0;
		while (p > 0 && rail[p-1] == rail[p]) p--;
	}

	return tryit(b+1, board[b+1]);
}

int check() {
	memset(railused, 0, sizeof(railused));
	railleft = 0;
	for (int i = 0; i < K; i++) railleft += rail[i];
	return tryit(0, board[0]);
}

int main()
{
	freopen("fence8.in", "r", stdin);
        freopen("fence8.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", &board[i]);
	sort(board, board+N);

	scanf("%d", &R);
	for (int i = 0; i < R; i++) scanf("%d", &rail[i]);
	sort(rail, rail+R);

	int max_board = *max_element(board, board+N);
	while (R > 0 && rail[R-1] > max_board) R--;

	int rail_sum[1024] = {0};
	for (int i = 1; i <= R; i++) rail_sum[i] = rail_sum[i-1] + rail[i-1];

	board_sum[0] = 0;
	for (int i = 1; i <= N; i++) board_sum[i] = board_sum[i-1] + board[i-1];

	while (R > 0 && rail_sum[R] > board_sum[N]) R--;

	board[N] = 0;

	int a, b;
	for (a = 0, b = R; a < b;) {
		K = (a + b + 1) / 2;
		if (check()) a = K; else b = K-1;
	}
	printf("%d\n", a);
	return 0;
}
