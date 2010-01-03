#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
using namespace std;

struct Bitmap {
	unsigned char data[(1<<25)/8+100];
	Bitmap() { memset(data, 0, sizeof(data)); }
	bool get(int i) { return (data[i >> 3] >> (i & 7)) & 1; }
	void set(int i) { data[i >> 3] |= 1 << (i & 7); }
} winning, seen;

int transpose(int state)
{
	int res = 0;
	for (int r = 0; r < 5; r++)
		for (int c = 0; c < 5; c++)
			res |= ((state >> (5*r+c)) & 1) << (5*c+r);
	return res;
}

bool eval(int state)
{
	if (seen.get(state)) {
		return winning.get(state);
	}

	int state1 = transpose(state);
	seen.set(state);
	seen.set(state1);

	int m, r, c, k, i, z;
	for (m = 0; m < 2; m++) {
		k = 0;
		for (r = 0; r < 5; r++) {
			for (c = 0; c < 5; c++, k++) {
				for (i = 1; c+i <= 5; i++) {
					z = ((1 << i) - 1) << k;
					if ((state & z) != z) break;

					if (!eval(state & ~z)) {
						winning.set(state);
						winning.set(state1);
						return true;
					}
				}
			}
		}

		swap(state, state1);
		if (state == state1) break;
	}

	return false;
}

int main()
{
	seen.set(0);
	winning.set(0);

	int T;
	for (scanf("%d", &T); T-- > 0;) {
		int mask = 0, x;
		for (int i = 0; i < 25; i++) {
			scanf("%d", &x);
			mask |= x << i;
		}
		printf(eval(mask) ? "winning\n" : "losing\n");
	}
}
