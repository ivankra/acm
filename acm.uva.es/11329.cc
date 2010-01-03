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
#include <ext/hash_map>
using namespace std;
using namespace __gnu_cxx;

hash_map<int, int> dist;
queue<int> Q;
int nextDist;

static inline void enqueue(int state) {
	if (dist.count(state) == 0) {
		dist[state] = nextDist;
		Q.push(state);
	}
}

int downtab[64], uptab[64], lefttab[64], righttab[64];

int rollDown(int dice) {
	static int s[] = { 3,0,1,2,4,5 };
	int res = 0;
	for (int i = 0; i < 6; i++)
		res |= ((dice >> s[i]) & 1) << i;
	return res;
}

int rollLeft(int dice) {
	static int s[] = { 4,1,5,3,2,0 };
	int res = 0;
	for (int i = 0; i < 6; i++)
		res |= ((dice >> s[i]) & 1) << i;
	return res;
}

static inline int swapBits(int x, int i, int j) {
	int a = (x >> i) & 1;
	int b = (x >> j) & 1;
	x &= ~((1 << i) | (1 << j));
	return x | (a << j) | (b << i);
}

int main()
{
	for (int i = 0; i < 64; i++) {
		downtab[i] = rollDown(i);
		uptab[i] = rollDown(rollDown(rollDown(i)));
		lefttab[i] = rollLeft(i);
		righttab[i] = rollLeft(rollLeft(rollLeft(i)));
	}

	for (int at = 0; at < 16; at++) {
		int state = (63 << 16) | (at << 22);
		Q.push(state);
		dist[state] = 0;
	}

	while (!Q.empty()) {
		int state = Q.front();
		Q.pop();
		nextDist = dist[state] + 1;
		int at = state >> 22, atY = at / 4, atX = at % 4;

		// down: reverse of roll up
		if (atY != 3) {
			int s = swapBits(state, at, 16);
			int newDice = downtab[(s >> 16) & 63];
			s = (s & 65535) | (newDice << 16) | ((at + 4) << 22);
			enqueue(s);
		}

		// up: reverse of roll down
		if (atY != 0) {
			int s = swapBits(state, at, 16);
			int newDice = uptab[(s >> 16) & 63];
			s = (s & 65535) | (newDice << 16) | ((at - 4) << 22);
			enqueue(s);
		}

		// left: reverse of roll right
		if (atX != 0) {
			int s = swapBits(state, at, 16);
			int newDice = lefttab[(s >> 16) & 63];
			s = (s & 65535) | (newDice << 16) | ((at - 1) << 22);
			enqueue(s);
		}

		// right: reverse of roll left
		if (atX != 3) {
			int s = swapBits(state, at, 16);
			int newDice = righttab[(s >> 16) & 63];
			s = (s & 65535) | (newDice << 16) | ((at + 1) << 22);
			enqueue(s);
		}
	}

	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		int diceAt = -1, mask = 0;
		for (int i = 0; i < 16; i++) {
			int c;
			do { c = getchar(); assert(c != EOF); } while (c != '.' && c != 'X' && c != 'D');

			if (c == 'D') {
				diceAt = i;
			}

			if (c == 'X')
				mask |= 1 << i;
		}
		assert(diceAt != -1);

		int state = mask | (diceAt << 22);
		if (dist.count(state) == 0) {
			printf("impossible\n");
		} else {
			printf("%d\n", dist[state]);
		}
	}
}
