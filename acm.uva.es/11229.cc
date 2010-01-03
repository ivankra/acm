#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int Get(int mask, int i, int j) {
	return (mask >> (2*(3*i+j))) & 3;
}

int Set(int mask, int i, int j, int value) {
	int s = 2*(3*i+j);
	return (mask & ~(3 << s)) | (value << s);
}

double prob[4][4][4];
int winner_memo[262144], got[262144], got_tick;
double memo[262144];

double rec(int cur, int state)
{
	if (got[state] == got_tick) return memo[state];
	got[state] = got_tick;

	double &res = memo[state];

	int winner;
	if (winner_memo[state] == -1) {
		winner = 0;

		// rows
		for (int i = 0; i < 3; i++) {
			int p = Get(state, i, 0) ;
			if (p != 0 && Get(state, i, 1) == p && Get(state, i, 2) == p) winner |= 1<<p;
		}

		// columns
		for (int i = 0; i < 3; i++) {
			int p = Get(state, 0, i) ;
			if (p != 0 && Get(state, 1, i) == p && Get(state, 2, i) == p) winner |= 1<<p;
		}

		// diagonals
		{ int p = Get(state, 0, 0);
		  if (p != 0 && Get(state, 1, 1) == p && Get(state, 2, 2) == p) winner |= 1<<p; }
		{ int p = Get(state, 2, 0);
		  if (p != 0 && Get(state, 1, 1) == p && Get(state, 0, 2) == p) winner |= 1<<p; }

		winner_memo[state] = winner;
	} else {
		winner = winner_memo[state];
	}

	int nfree = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (Get(state, i, j) == 0) nfree++;

	if (winner != 0 || nfree == 0) {
		if (winner == 0) return res = 0;
		if (winner == 2+3) return res = 0;
		if (winner == 2) return res = 1;
		return res = 0;
	}

	res = (cur == 1 ? 0.0 : 1.0);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (Get(state, i, j) != 0) continue;

			int other = cur == 1 ? 2 : 1;
			double p = prob[cur][i][j];

			double t =   p   * rec(other, Set(state, i, j, cur)) +
				       (1-p) * rec(other, Set(state, i, j, other));

			if (cur == 1)
				res >?= t;
			else
				res <?= t;
		}
	}

	return res;
}

int main() {
	int T;
	scanf("%d", &T);

	memset(winner_memo, 0xff, sizeof(winner_memo));
	memset(got, 0, sizeof(got));
	got_tick = 42;

	for (int cs = 1; cs <= T; cs++) {
		for (int p = 1; p <= 2; p++) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					scanf("%lf", &prob[p][i][j]);
					prob[p][i][j] /= 100.0;
				}
			}
		}

		got_tick++;
		printf("Case #%d: %.2f\n", cs, rec(1, 0) * 100.0);
	}
}
