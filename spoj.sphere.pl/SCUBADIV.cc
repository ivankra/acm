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

int need1, need2, N;
int vol1[2000], vol2[2000], weight[2000];

int best[80][80], next[80][80];

int solve()
{
	memset(best, 0x3f, sizeof(best));
	best[0][0] = 0;

	for (int i = 0; i < N; i++) {
		memcpy(next, best, sizeof(best));
		for (int a = 0; a <= need1; a++)
			for (int b = 0; b <= need2; b++)
				next[min(need1, a + vol1[i])][min(need2, b + vol2[i])] <?= best[a][b] + weight[i];
		memcpy(best, next, sizeof(best));
	}

	return best[need1][need2];
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d", &need1, &need2, &N);
		for (int i = 0; i < N; i++)
			scanf("%d %d %d", &vol1[i], &vol2[i], &weight[i]);
		printf("%d\n", solve());
	}
}
