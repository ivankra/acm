#include <cstdio>
#include <cctype>
#include <cassert>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int N;
int adj[2048][2048], deg[2048];
int kid[2048], sib[2048], up[2048];
int out[2048][5], outsize;

void move(int a, int b, int c = 0, int d = 0) {
	int n;
	if (c == 0) n = 1;
	else if (d == 0) n = 2;
	else n = 3;
	out[outsize][0] = n;
	out[outsize][1] = a;
	out[outsize][2] = b;
	out[outsize][3] = c;
	out[outsize][4] = d;
	outsize++;
}

void solve(int x) {
	if (kid[x] == 0) {
		if (sib[x] == 0) {
			move(x, up[x]);
		} else {
			move(x, up[x], sib[x]);
			solve(sib[x]);
		}
		return;
	}

	if (kid[kid[x]] == 0) {
		move(x, kid[x]);
	} else {
		move(x, kid[x], kid[kid[x]]);
		solve(kid[kid[x]]);
	}

	// now at: kid[x];

	int y = kid[x];
	while (sib[y] != 0) {
		if (kid[sib[y]] == 0) {
			move(y, x, sib[y]);
			y = sib[y];
		} else {
			move(y, x, sib[y], kid[sib[y]]);
			solve(kid[sib[y]]);
			y = sib[y];
		}
	}

	// now at y, last kid of x

	if (sib[x] != 0) {
		move(y, x, sib[x]);
		solve(sib[x]);
	} else {
		move(y, x, up[x]);
	}
}

int dfs(int x) {
	if (deg[x] < 0) return 0;

	int m = deg[x], res = 1;
	deg[x] = -1;
	kid[x] = sib[x] = up[x] = 0;

	for (int i = 0; i < m; i++) {
		int y = adj[x][i];
		if (deg[y] >= 0) {
			res += dfs(y);
			sib[y] = kid[x];
			kid[x] = y;
			up[y] = x;
		}
	}

	return res;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		if (cs > 1) printf("\n");

		int M;
		assert(scanf("%d %d", &N, &M) == 2);
		assert(2 <= N && N <= 2000);

		for (int x = 1; x <= N; x++) deg[x] = 0;
		for (int i = 0; i < M; i++) {
			int x, y;
			assert(scanf("%d %d", &x, &y) == 2);
			assert(1 <= x && x <= N);
			assert(1 <= y && y <= N);
			if (x == y) continue;
			adj[x][deg[x]++] = y;
			adj[y][deg[y]++] = x;
		}

		if (dfs(1) != N) {
			printf("Impossible\n");
			continue;
		}

		outsize = 0;
		move(1, kid[1]);

		solve(kid[1]);

		for (int i = 0; i < outsize; i++) {
			printf("%d", out[i][0]);
			for (int j = 0; j <= out[i][0]; j++)
				printf(" %d", out[i][1+j]);
			printf("\n");
		}
	}
}
