#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long int64;

int Cnt[512][512], Up[512][512], Left[512][512];

int64 solve(int r1, int c1, int r2, int c2) {
	int64 L = 0, R = 0, cost = 0;
	int x = c1;

	for (int c = c1+1; c <= c2; c++) {
		int t = Up[r2][c] - Up[r1-1][c];
		R += t;
		cost += (c-x) * (int64)t;
	}

	int64 best1 = cost;
	int a = 0, b = Up[r2][x] - Up[r1-1][x];
	while (++x <= c2) {
		a = b;
		b = Up[r2][x] - Up[r1-1][x];

		cost += L + a - R;
		L += a;
		R -= b;

		best1 <?= cost;
	}

//---
	L = R = cost = 0;
	int y = r1;

	for (int r = r1+1; r <= r2; r++) {
		int t = Left[r][c2] - Left[r][c1-1];
		R += t;
		cost += (r-y) * (int64)t;
	}

	int64 best2 = cost;
	a = 0;
	b = Left[y][c2] - Left[y][c1-1];
	while (++y <= r2) {
		a = b;
		b = Left[y][c2] - Left[y][c1-1];

		cost += L + a - R;
		L += a;
		R -= b;

		best2 <?= cost;
	}

	return best1 + best2;
}

int main() {
	int T, Q, R, C;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d", &R, &C, &Q);

		memset(Cnt, 0, sizeof(Cnt));
		for (int r = 1; r <= R; r++)
			for (int c = 1; c <= C; c++)
				scanf("%d", &Cnt[r][c]);

		memset(Left, 0, sizeof(Left));
		memset(Up, 0, sizeof(Up));
		for (int r = 1; r <= R; r++) {
			for (int c = 1; c <= C; c++) {
				Up[r][c] = Up[r-1][c] + Cnt[r][c];
				Left[r][c] = Left[r][c-1] + Cnt[r][c];
			}
		}

		printf("Test Case %d:\n", cs);
		for (int q = 1; q <= Q; q++) {
			int r1, r2, c1, c2;
			scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
			if (r1 > r2) swap(r1, r2);
			if (c1 > c2) swap(c1, c2);
			printf("%d %lld\n", q, (long long)solve(r1, c1, r2, c2));
		}
		printf("\n");
	}
}
