#include <cstdio>
#include <algorithm>
using namespace std;

char mat[1024][1024], res[1024][1024];
int N;

int solve() {
	int cn = 0, xrow[1024], xcol[1024];

	for (int row = 0; row < N; row++) {
		xrow[row] = 0;
		for (int c = 0; c < N; c++)
			xrow[row] ^= mat[row][c];
	}

	for (int col = 0; col < N; col++) {
		xcol[col] = 0;
		for (int r = 0; r < N; r++)
			xcol[col] ^= mat[r][col];
	}

	for (int row = 0; row < N; row++)
	for (int col = 0; col < N; col++) {
		int t = mat[row][col] ^ xrow[row] ^ xcol[col];
		res[row][col] = (res[row][col] << 1) + t;
		cn += t;
	}
	return cn;
}

int main() {
	scanf("%d ", &N);
	for (int i = 0; i < N; i++) {
		gets(mat[i]);
		for (int j = 0; j < N; j++)
			mat[i][j] = (mat[i][j] == 'W') ? 1 : 0;
	}

	memset(res, 0, sizeof(res));
	int r0 = solve();
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			mat[i][j] ^= 1;
	int r1 = solve();

	int m = (r0 < r1) ? 2 : 1;
	printf("%d\n", min(r0, r1));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (res[i][j] & m)
				printf("%d %d\n", i+1, j+1);
	return 0;
}
