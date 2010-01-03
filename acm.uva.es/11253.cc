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

int DX[4] = { 1, 0, -1, 0 };
int DY[4] = { 0, -1, 0, 1 };

struct State {
	int x, y, d;
};

int levelSize(int n) { return (1 << (n+1)) - 1; }

/*
string gen(int level, int rev)
{
	if (rev == 0) {
		if (level == 0) return "1";
		return gen(level-1, 0) + "1" + gen(level-1, 1);
	} else {
		if (level == 0) return "0";
		return gen(level-1, 0) + "0" + gen(level-1, 1);
	}
}
*/

State execute1(State state, int digit)
{
	state.x += DX[state.d];
	state.y += DY[state.d];
	state.d = (state.d + (digit == 1 ? 3 : 1)) % 4;
	return state;
}

bool got[50][2][4];
State memo[50][2][4];

State execute(State state0, int level, int rev, int n0)
{
	int n = n0;
	State state = state0;
	state.x = 0;
	state.y = 0;
	assert(0 <= n && n <= levelSize(level));

	if (n == 0) return state;

	if (n0 == levelSize(level)) {
		if (got[level][rev][state0.d]) {
			state = memo[level][rev][state0.d];
			state.x += state0.x;
			state.y += state0.y;
			return state;
		}
	}

	if (rev == 0) {
		if (level == 0) {
			state = execute1(state, 1);
		} else {
			state = execute(state, level-1, 0, min(levelSize(level-1), n));
			n -= levelSize(level-1);
			if (n > 0) {
				state = execute1(state, 1);
				n--;
				if (n > 0) {
					state = execute(state, level-1, 1, n);
				}
			}
		}
	} else {
		if (level == 0) {
			state = execute1(state, 0);
		} else {
			state = execute(state, level-1, 0, min(levelSize(level-1), n));
			n -= levelSize(level-1);
			if (n > 0) {
				state = execute1(state, 0);
				n--;
				if (n > 0) {
					state = execute(state, level-1, 1, n);
				}
			}
		}
	}

	if (n0 == levelSize(level)) {
		got[level][rev][state0.d] = true;
		memo[level][rev][state0.d] = state;
	}

	state.x += state0.x;
	state.y += state0.y;
	return state;
}

int main()
{
	int n;
	while (scanf("%d", &n) == 1 && n >= 0) {
		State state = { 0, 0, 0 };
		state = execute(state, 30, 0, n);
		printf("(%d,%d)\n", state.x, state.y);
	}
}
