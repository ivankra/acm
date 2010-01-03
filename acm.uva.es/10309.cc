#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

int Map[16];

int bitcnt(int x) {
	int r = 0;
	while (x > 0) { r++; x &= x - 1; }
	return r;
}

int check(int x) {
	int a[16], W = (1 << 10) - 1, ret = 0;
	for (int i = 0; i < 10; i++) a[i] = Map[i];
	for (int r = 0; r < 10; r++) {
		ret += bitcnt(x);
		a[r+1] ^= x;
		x = (a[r] ^= (x ^ (x << 1) ^ (x >> 1)) & W);
	}
	return (a[9] == 0 ? ret : -1);
}

int solve() {
	for (int i = 0; i < 10; i++) {
		Map[i] = 0;
		for (int j = 0; j < 10; j++) {
			int c;
			for (;;) {
				c = getchar();
				assert(c != EOF);
				if (c == '#' || c == 'o' || c == 'O') break;
			}
			Map[i] |= ((c == '#') ? 0 : 1) << j;
		}
	}

	int ret = -1;
	for (int head = 0; head < (1 << 10); head++) {
		int x = check(head);
		if (x >= 0 && (ret < 0 || ret > x)) ret = x;
	}
	return ret;
}

int main()
{
	char name[256];
	while (scanf(" %s", name) == 1 && strcmp(name, "end") != 0)
		printf("%s %d\n", name, solve());
	return 0;
}
