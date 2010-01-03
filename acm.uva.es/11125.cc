#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int N;

int Get(int S, int K) { return ((S>>(3*K))&7); }
int Set(int S, int K, int X) { return (S & ~(7 << (3*K))) | (X << 
(3*K)); }

long long memo[4][4][4096][4][4];

int start_col, start_sz;

long long f(int state, int last_col, int last_sz) {
	long long &res = memo[start_col][start_sz][state][last_col][last_sz];
	if (res != -1) return res;

	if (state == 0)
		return res = 1;

	res = 0;
	for (int col = 0; col < N; col++) {
		if (col == last_col) continue;
		for (int sz = 1; sz <= 3 && sz <= Get(state, col); sz++) {
			if (sz == last_sz) continue;

			int s1 = Set(state, col, Get(state, col)-sz);
			if (s1 == 0) {
				if (col == start_col) continue;
				if (sz == start_sz) continue;
			}

			res += f(s1, col, sz);
		}
	}

	return res;
}

int main() {
	int T;
	scanf("%d", &T);

	memset(memo, 0xff, sizeof(memo));

	for (int cs = 1; cs <= T; cs++) {
		if (scanf("%d", &N) != 1) break;

		int s = 0;
		for (int i = 0; i < N; i++) {
			int x;
			scanf("%d", &x);
			s |= x << (3*i);
		}

		long long res = 0;
		for (int col = 0; col < N; col++) {
			for (int sz = 1; sz <= 3 && sz <= Get(s, col); sz++) {
				start_col = col;
				start_sz = sz;
				int s1 = Set(s, col, Get(s, col)-sz);
				res += f(s1, col, sz);
			}
		}

		if (s == 0) { res = 1; }

		printf("%lld\n", res);
	}
}
