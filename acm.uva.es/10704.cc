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
#include <queue>
using namespace std;

struct Block {
	int type;	// H/V
	int len, row, col;
	unsigned long long masks[20];
} block[100];

int N;

struct State {
	long long encoding;

	int encGet(int i) const {
		return (encoding >> (3 * i)) & 7;
	}

	void encSet(int i, int val) {
		encoding &= ~(7LL << (3*i));
		encoding |= ((unsigned long long)val) << (3*i);
	}

	int getRow(int i) const {
		return block[i].type == 'H' ? block[i].row : encGet(i);
	}

	int getCol(int i) const {
		return block[i].type == 'V' ? block[i].col : encGet(i);
	}

	void setRow(int i, int newRow) {
		if (block[i].type == 'V') encSet(i, newRow);
	}

	void setCol(int i, int newCol) {
		if (block[i].type == 'H') encSet(i, newCol);
	}

	bool operator <(const State &other) const {
		return encoding < other.encoding;
	}
};

map<State, int> stateMap;

int solve()
{
	State source;
	for (int i = 0; i < N; i++) {
		source.setRow(i, block[i].row);
		source.setCol(i, block[i].col);
	}

	stateMap.clear();
	stateMap[source] = 0;

	queue<State> Q;
	Q.push(source);

	while (!Q.empty()) {
		State state = Q.front();
		Q.pop();
		int curDist = stateMap[state];

		if (state.getCol(0) == 4) return curDist+1;

		unsigned long long mask = 0;
		for (int i = 0; i < N; i++) {
			assert((mask & block[i].masks[state.encGet(i)]) == 0);
			mask |= block[i].masks[state.encGet(i)];
		}

/*printf("mask=%.16llX col0=%d\n",mask,state.getCol(0));
for (int y = 0; y < 6; y++) {
	for (int x = 0; x < 6; x++) {
		if ((mask & (1ULL << (8*y+x))) != 0) putchar('*'); else putchar('.');
	}
	printf("\n");
}
exit(0);*/

		for (int i = 0; i < N; i++) {
			for (int dir = -1; dir <= 1; dir += 2) {
				for (int delta = 1; delta <= 6; delta++) {
					int newVal = state.encGet(i) + dir*delta;
					if (newVal < 0 || newVal+block[i].len > 6) break;

					if (((mask & ~block[i].masks[state.encGet(i)]) &
						block[i].masks[newVal]) != 0)
						break;

					if (i == 0 && newVal == 4) return curDist+1;

					State newState = state;
					newState.encSet(i, newVal);
					if (stateMap.count(newState) == 0) {
						stateMap[newState] = curDist + 1;
						Q.push(newState);
					}
				}
			}
		}
	}

	return -1;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		memset(block, 0, sizeof(block));
		N = 1;
		block[0].type = 'H';
		block[0].len = 2;
		scanf("%d %d", &block[0].row, &block[0].col);

		for (int i = 2; i <= 5; i++) {
			int cnt;
			scanf("%d", &cnt);
			for (int j = 0; j < cnt; j++) {
				scanf("%d %d", &block[N].row, &block[N].col);
				block[N].type = (i == 2 || i == 3) ? 'V' : 'H';
				block[N].len = (i == 2 || i == 4) ? 2 : 3;
				N++;
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j <= 6; j++) {
				block[i].masks[j] = 0;
				for (int k = 0; k < block[i].len; k++) {
					int x, y;
					if (block[i].type == 'H') {
						y = block[i].row;
						x = j + k;
					} else {
						y = j + k;
						x = block[i].col;
					}
					block[i].masks[j] |= 1ULL << (8*y+x);
				}
			}
		}

		int res = solve();
		printf("The minimal number of moves to solve puzzle %d is %d.\n", cs, res);
	}
}
