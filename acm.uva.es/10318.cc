#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

#define INF 1000000

int mask[3], nrows, ncols;
int memo[5][32][32];

int f(int row, int prev_, int cur_) {
	if (row == nrows) {
		if (prev_ != (1<<ncols)-1) return INF;
		return 0;
	}

	int &res = memo[row][prev_][cur_];
	if (res != -1) return res;

	res = INF;

	for (int sw = 0; sw < (1<<ncols); sw++) {
		int prev = prev_;
		int cur = cur_;
		int next = 0;
		int cost = 0;

		for (int i = 0; i < ncols; i++) {
			if ((sw & (1 << i)) == 0) continue;
			cost++;
			prev ^= (mask[0] << i) >> 1;
			cur  ^= (mask[1] << i) >> 1;
			next ^= (mask[2] << i) >> 1;
		}

		prev &= (1 << ncols) - 1;
		cur &= (1 << ncols) - 1;
		next &= (1 << ncols) - 1;
		if (row > 0 && prev != (1 << ncols) - 1) continue;

		res = min(res, cost + f(row+1, cur, next));
	}

	return res;
}

int first;

void recover(int row, int prev_, int cur_) {
	if (row == nrows) return;

	int res = f(row, prev_, cur_);

	for (int sw = 0; sw < (1<<ncols); sw++) {
		int prev = prev_;
		int cur = cur_;
		int next = 0;
		int cost = 0;

		for (int i = 0; i < ncols; i++) {
			if ((sw & (1 << i)) == 0) continue;
			cost++;
			prev ^= (mask[0] << i) >> 1;
			cur  ^= (mask[1] << i) >> 1;
			next ^= (mask[2] << i) >> 1;
		}

		prev &= (1 << ncols) - 1;
		cur &= (1 << ncols) - 1;
		next &= (1 << ncols) - 1;
		if (row > 0 && prev != (1 << ncols) - 1) continue;

		if (res == cost + f(row+1, cur, next)) {
			for (int i = 0; i < ncols; i++) {
				if ((sw & (1 << i)) == 0) continue;
				if (first) first = 0; else printf(" ");
				printf("%d", 1+row*ncols+i);
			}
			recover(row+1, cur, next);
			return;
		}
	}
	abort();
}

int main()
{
	for (int cs = 1; scanf("%d %d", &nrows, &ncols) == 2 && nrows > 0; cs++) {
		for (int i = 0; i < 3; i++) {
			mask[i] = 0;
			for (int j = 0; j < 3; j++) {
				char c;
				scanf(" %c", &c);
				mask[i] |= (c == '*' ? 1 : 0) << j;
			}
		}

		memset(memo, 0xff, sizeof(memo));
		printf("Case #%d\n", cs);
		if (f(0, 0, 0) == INF) {
			printf("Impossible.\n");
		} else {
			first = 1;
			recover(0, 0, 0);
			printf("\n");
		}
	}
}
