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

int value[] = {
	10, 20, 50, 100, 200,
	500, 1000, 2000, 5000, 10000,
	20000, 50000, 100000, 200000, 500000
};

int perc[4], limit, sum[1<<15], nbits[1<<15], mini[1<<15], maxi[1<<15];
char got[1<<15];
double prob[1<<15], prize[1<<15];
int choose[5][1536], choose_n[5]={0,0,0,0,0};

void rec(int round, int mask) {
	if (got[mask]) return;
	got[mask] = 1;

	if (round == 4) {
		prize[mask] = sum[mask] / 2.0;
		prob[mask] = 0;
		if (mini[mask] >= limit) prob[mask] += 0.5;
		if (maxi[mask] >= limit) prob[mask] += 0.5;
		return;
	}

	prob[mask] = 0;
	prize[mask] = 0;

	int *ch = choose[round == 0 ? 4 : 3];
	int ch_n = choose_n[round == 0 ? 4 : 3];

	int denom = 0;
	prob[mask] = 0;
	prize[mask] = 0;

	for (int ch_i = 0; ch_i < ch_n; ch_i++) {
		int c = ch[ch_i];
		if ((mask & c) != c) continue;

		int deal = (sum[mask^c] * perc[round]) / (100 * nbits[mask^c]);
		if (deal >= limit) {
			prob[mask] += 1.0;
			prize[mask] += deal;
		} else {
			rec(round+1, mask^c);
			prob[mask] += prob[mask^c];
			prize[mask] += prize[mask^c];
		}

		denom++;
	}

	prob[mask] /= denom;
	prize[mask] /= denom;
}

int main() {
	for (int mask = 0; mask < 32768; mask++) {
		sum[mask] = 0;
		nbits[0] = 0;
		mini[mask] = 1<<30;
		maxi[mask] = 0;
		for (int i = 0; i < 15; i++) {
			if ((mask & (1 << i)) == 0) continue;
			sum[mask] += value[i];
			nbits[mask]++;
			mini[mask] <?= value[i];
			maxi[mask] >?= value[i];
		}
		if (nbits[mask] <= 4)
			choose[nbits[mask]][choose_n[nbits[mask]]++] = mask;
	}

	for (;;) {
		int t = scanf("%d %d %d %d %d", &limit, &perc[0], &perc[1], &perc[2], &perc[3]);
		if (t != 5 || limit <= 0) break;

		memset(got, 0, sizeof(got));
		int m = (1<<15)-1;
		rec(0, m);
		printf("%.10f %.10f\n", prob[m], prize[m]);
	}
}
