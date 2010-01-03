#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

struct Rock {
	char kind;
	int dist;
} rock[128];

int memo[128][128], N;

int f(int i, int j) {
	int &res = memo[i][j];
	if (res != -1) return res;

	res = 1<<30;
	if (i > N && j > N) return res = 0;

	if (i <= j) {
		for (int t = i; t <= N+1; t++) {
			if (t == j && rock[t].kind != 'B') continue;
			res <?= max(abs(rock[t].dist - rock[i].dist), f(t, j));
		}
	} else {
		for (int t = j; t <= N+1; t++) {
			if (t == i && rock[t].kind != 'B') continue;
			res <?= max(abs(rock[t].dist - rock[j].dist), f(i, t));
		}
	}

	return res;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d", &N) == 1; cs++) {
		rock[0].kind = 'B'; rock[0].dist = 0;
		rock[N+1].kind = 'B';
		scanf("%d", &rock[N+1].dist);

		for (int i = 1; i <= N; i++) {
			scanf(" %c - %d", &rock[i].kind, &rock[i].dist);
			assert(rock[i-1].dist <= rock[i].dist);
			assert(rock[i].dist <= rock[N+1].dist);
		}

		memset(memo, 0xff, sizeof(memo));
		printf("Case %d: %d\n", cs, f(0, 0));
	}
}
