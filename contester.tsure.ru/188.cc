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

enum { MAXN = 10010, INF = 0x1fffffff };
int cost[MAXN], way[MAXN], arg1[MAXN], arg2[MAXN];

void recover(int N, bool br) {
	if (N == 1) {
		printf("1");
	} else if (way[N] == '+' || way[N] == '*') {
		if (br) printf("(");
		recover(arg1[N], (way[N] == '*' && way[arg1[N]] == '+'));
		printf("%c", way[N]);
		recover(arg2[N], (way[N] == '*' && way[arg2[N]] == '+'));
		if (br) printf(")");
	} else {
		assert(way[N] == '!');
		recover(arg1[N], true);
		printf("!");
	}
}

int main() {
	memset(way, 0, sizeof(way));
	for (int i = 1, n = 1; n <= MAXN; n *= ++i) {
		way[n] = '!';
		arg1[n] = i;
	}

	cost[0] = INF;
	cost[1] = 1; way[1] = '1';

	for (int N = 2; N < MAXN; N++) {
		cost[N] = (N > 2 && way[N] == '!' ? cost[arg1[N]] : INF);

#define $(COST, A, OP, B) {if((COST)<cost[N]){cost[N]=COST;way[N]=OP;arg1[N]=A;arg2[N]=B;}}
		$(1 + cost[N-1], N-1, '+', 1)

		for (int m = 2; m+m <= N; m++)
			$(cost[m] + cost[N-m], m, '+', N-m)

		for (int d = 2; d*d <= N; d++) {
			if (N % d != 0) continue;
			$(cost[d] + cost[N/d], d, '*', N/d)
		}
	}

	int N;
	cin >> N;
	recover(N, false);
	printf("\n");
}
