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

struct BoxType {
	int m, price;
	bool operator <(const BoxType &other) const {
		return m < other.m;
	}
};

struct Box {
	int m, count;
	bool operator <(const Box &other) const {
		return m < other.m;
	}
};

BoxType boxTypes[2000];
Box boxes[2000];
int M, N;
int extraCost;

int got[1002][1024][2], got_id;
long long memo[1002][1024][2], INF = 1LL<<60;

long long rec(int i, int j, int flag) {
	long long &res = memo[i][j][flag];
	if (got[i][j][flag] == got_id) return res;
	got[i][j][flag] = got_id;

	res = INF;
	if (j == N) return res = 0;
	if (i == M) return res = INF;

	if (flag == 0)
		res <?= rec(i, j, 1) + extraCost;

	res <?= rec(i+1, j, 0);
	if (flag == 1 && boxes[j].m <= boxTypes[i].m) {
		res <?= boxes[j].count * (long long)boxTypes[i].price + rec(i, j+1, 1);
	}

	return res;
}

int main()
{
	memset(got, 0, sizeof(got));
	for (int cs = 1; scanf("%d %d %d", &extraCost, &M, &N) == 3; cs++) {
		if (extraCost == 0 && M == 0 && N == 0) break;

		for (int i = 0; i < M; i++)
			scanf("%d %d", &boxTypes[i].m, &boxTypes[i].price);
		sort(boxTypes, boxTypes+M);

		for (int i = 0; i < N; i++)
			scanf("%d %d", &boxes[i].m, &boxes[i].count);
		sort(boxes, boxes+N);

		got_id = cs + 100;
		long long res = rec(0, 0, 0);
		printf("case %d: ",cs);
		if (res >= INF)
			printf("not possible\n");
		else
			printf("%lld\n", res);
	}
}
