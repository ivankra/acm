#include <algorithm>
#include <vector>
#include <sstream>
#include <cmath>
#include <cassert>
#include <cstdio>
using namespace std;

typedef unsigned long long num;

int mat[64][64], N;

int solveMod(int mod, int inv[]) {
	int a[64][64];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			a[i][j] = ((mat[i][j] % mod) + mod) % mod;

	int det = 1;
	for (int i = 0; i < N; i++) {
		int r;
		for (r = i; r < N && a[r][i] == 0; r++);
		if (r >= N) return 0;

		if (i != r) {
			for (int k = 0; k < N; k++) swap(a[i][k], a[r][k]);
			det = (mod - det) % mod;
		}

		det = (det * a[i][i]) % mod;
		for (int j = i+1; j < N; j++) {
			int t = (a[j][i] * inv[a[i][i]]) % mod;
			for (int k = 0; k < N; k++) {
				a[j][k] = ((a[j][k] - a[i][k] * t) % mod + mod) % mod;
			}
		}
	}

	return det;
}

int main() {
	const int NMOD = 7;
	int imod[NMOD] = { 223, 227, 229, 233, 239, 241, 251 }, itab[NMOD][256];

	for (int i = 0; i < NMOD; i++) {
		for (int x = 0; x < imod[i]; x++) {
			int y;
			for (y = imod[i]-1; y > 0; y--)
				if (((x*y) % imod[i]) == 1) break;
			itab[i][x] = y;
		}
	}

	int M, K;
	while (scanf("%d %d %d", &N, &M, &K) == 3 && N > 0) {
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				mat[i][j] = (i == j ? 0 : -1);

		for (int i = 0; i < M; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			mat[x-1][y-1] = mat[y-1][x-1] = 0;
		}

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (i != j) mat[i][i] -= mat[i][j];

		N--;

		unsigned long long M = 1, res = 0;
		for (int i = 0; i < NMOD; i++) M *= imod[i];

		for (int i = 0; i < NMOD; i++) {
			int m = imod[i];
			int x = solveMod(m, itab[i]);
			//printf("mod %d: %d\n", imod[i], x);
			res = (res + x * (((M/m) * itab[i][(M/m)%m]) % M)) % M;
		}
		printf("%llu\n", res);
	}
}
