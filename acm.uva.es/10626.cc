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

int dp[160][160][60];

int main()
{
	int T;
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		int cokes, N[3];
		scanf("%d %d %d %d", &cokes, &N[0], &N[1], &N[2]);

		int money1 = N[0] + 5*N[1] + 10*N[2];
		int money2 = money1 - 8 * cokes;
		assert(money2 >= 0);

		memset(dp, 0x1f, sizeof(dp));
		for (int C = 0; C <= cokes; C++) {
			int money = money1 - 8*(cokes-C);
			for (int fives = 0; fives <= 150; fives++)
			for (int tens = 0; tens <= N[2]; tens++) {
				int ones = money - 5*fives - 10*tens;
				if (ones < 0) continue;

				int &res = dp[C][fives][tens];

				if (C == 0) {
					res = 0;
					continue;
				}

				if (tens >= 1)
					res <?= 1 + dp[C-1][fives][tens-1];

				if (tens >= 1 && ones >= 3)
					res <?= 4 + dp[C-1][fives+1][tens-1];

				if (fives >= 1 && ones >= 3)
					res <?= 4 + dp[C-1][fives-1][tens];

				if (fives >= 2)
					res <?= 2 + dp[C-1][fives-2][tens];

				if (ones >= 8)
					res <?= 8 + dp[C-1][fives][tens];
			}
		}

		printf("%d\n", dp[cokes][N[1]][N[2]]);
	}
}
