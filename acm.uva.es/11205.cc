// algorithm: brute force subset of active LEDs
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
typedef vector<int> VI;
typedef vector<VI> VVI;

int seen[65536];

int main() {
	int T, P, N;
	cin >> T;

	memset(seen, 0, sizeof(seen));
	int tick = 42;

	for (int cs = 1; cs <= T; cs++) {
		cin >> P >> N;

		int sym[200];
		for (int i = 0; i < N; i++) {
			sym[i] = 0;
			for (int j = 0, x = 0; j < P; j++) {
				cin >> x;
				sym[i] = sym[i] * 2 + x;
			}
		}

		int best = P;
		for (int mask = 0; mask < (1 << P); mask++) {
			int s = 0;
			for (int i = 0; i < P; i++)
				s += (mask >> i) & 1;
			if (s >= best) continue;

			tick++;
			for (int i = 0; i < N; i++) {
				if (seen[sym[i] & mask] == tick) goto skip;
				seen[sym[i] & mask] = tick;
			}

			best = s;
skip:;
		}

		cout << best << endl;
	}
}
