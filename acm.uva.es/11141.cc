#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

struct Cube {
	int a[3], b[3];
} C[256];

int N, used, next[10], first;
int memo[201][64][64], got[201][64][64], got_id;

void add(int &x, int y) {
	x += y;
	if (x >= 1000000000) x -= 1000000000;
}

int f(int pos, int open, int close) {
	if (pos == N)
		return (open == 0) ? 0 : 1;

	int &res = memo[pos][open][close];
	if (got[pos][open][close] == got_id) return res;
	got[pos][open][close] = got_id;

	res = f(pos+1, open, close);

	for (int i = 0; i < 3; i++) {
		int a = C[pos].a[i], b = C[pos].b[i];
		if (a < 0) continue;

		if (a == b) {
			if (close & (1 << a)) goto skip;
			add(res, f(pos+1, open|(1<<a), close));
		} else {
			if (close & (1 << a)) goto skip;

			int m = 0;
			for (int c = a+1; c < b; c++) m |= 1 << c;

			if ((open & (m|(1<<b))) != 0) goto skip;
			add(res, f(pos+1, open|(1<<a)|m|(1<<b), close|(1<<a)|m));
		}
skip:;
	}

	return res;
}

int main()
{
	int T;

	memset(got, 0, sizeof(got));
	got_id = 1;

	for (scanf("%d", &T); T-- > 0 && scanf("%d", &N) == 1;) {
		assert(1 <= N && N <= 200);
		for (int i = 0; i < N; i++) {
			int x[6];
			for (int j = 0; j < 6; j++) {
				scanf("%d", &x[j]);
				assert(1 <= x[j] && x[j] <= 6);
				x[j]--;
			}

			for (int j = 0; j < 3; j++) {
				C[i].a[j] = x[j];
				C[i].b[j] = x[5-j];
				if (C[i].a[j] > C[i].b[j]) swap(C[i].a[j], C[i].b[j]);
			}

			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < j; k++) {
					if (C[i].a[j] == C[i].a[k] && C[i].b[j] == C[i].b[k]) {
						C[i].a[j] = -1;
						C[i].b[j] = -1;
						break;
					}
				}
			}
		}

		got_id++;
		printf("%d\n", f(0,0,0));
	}
}
