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

int N, best, cur;
unsigned mask[1000][4], goal[4];

void rec(int i, unsigned a0, unsigned a1, unsigned a2)
{
	if (a0 == goal[0] && a1 == goal[1] && a2 == goal[2]) {
		if (cur < best) best = cur;
		return;
	}

	if (i >= N || cur+1 >= best) return;

	rec(i+1, a0, a1, a2);

	++cur;
	rec(i+1, a0 | mask[i][0], a1 | mask[i][1], a2 | mask[i][2]);
	--cur;
}

int main() {
	int h, w;

	for (int cs = 1; scanf("%d %d", &h, &w) == 2 && h > 1 && w > 1; cs++) {
		N = h * w;

		memset(mask, 0, sizeof(mask));
		memset(goal, 0, sizeof(goal));

		for (int i = 0; i < N; i++) {
			char ch;
			scanf(" %c", &ch);
			if (ch == 'X')
				goal[i>>5] |= 1U << (i & 31);
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				int dy = i/w - j/w;
				int dx = i%w - j%w;
				if (dx == 0 || dy == 0 || dx == dy || dx == -dy) {
					mask[i][j >> 5] |= 1U << (j & 31);
				}
			}

			for (int j = 0; j < 3; j++)
				mask[i][j] &= goal[j];
		}

		best = 6;
		cur = 0;
		rec(0, 0,0,0);
		printf("Case %d: %d\n", cs, best);
	}
}
