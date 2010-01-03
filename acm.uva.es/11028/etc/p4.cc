#include <cstdio>
#include <algorithm>
using namespace std;

int memo[20][1<<19];

int doit(int prev, int avail) {
	int &ret = memo[prev][avail>>1];
	if (ret != -1) return ret;
	if (avail == 0) return ret = 0;

	ret = -1;
	for (int x = 1; x < 20; x++) {
		if (avail & (1 << x)) {
			ret >?= prev * x + doit(x, avail ^ (1 << x));
		}
	}
	return ret;
}

int main() {
	memset(memo, 0xff, sizeof(memo));
	for (int n = 1; n <= 20; n++) {
		printf("n=%d: max=%d\n", n, doit(0, (1<<n)-1-1));
	}
}
