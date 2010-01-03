#include <cstdio>
#include <algorithm>
using namespace std;

int minsum[20][1<<19];
int maxsum[20][1<<19];

int main() {
	memset(minsum, 0, sizeof(minsum));
	memset(maxsum, 0, sizeof(maxsum));
	for (int n = 1; n <= 20; n++) {
		printf("n=%d\n",n);
		for (int mask = (1<<n)-1; mask >= 1; mask -= 2)
		for (int prev = 0; prev < n; prev++) if (mask & (1 << prev)) {
			minsum[prev][mask] = 1<<20;
			maxsum[prev][mask] = 0;
			for (int x = 1; x < n; x++) {
				if ((mask & (1 << x)) == 0) {
					minsum[prev][mask] <?= prev*x + minsum[x][prev^(1<<x)];
					maxsum[prev][mask] >?= prev*x + maxsum[x][prev^(1<<x)];
				}
                        }
		}

		printf("%d: min=%d max=%d\n", n, minsum[0][1], maxsum[0][1]);
	}
}
