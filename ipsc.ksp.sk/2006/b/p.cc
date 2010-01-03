#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

typedef unsigned long long u64;

int a[120000], n;

int main() {
	int T;
	for (scanf("%d", &T); T-- > 0 && scanf(" %d", &n) == 1;) {
		assert(1 <= n && n <= 110000);
		for (int i = 0; i < n; i++) {
			a[i] = -1;
			int j = scanf(" %*s %d", &a[i]);
			assert(j >= 1);
			assert(1 <= a[i] && a[i] <= n);
			a[i]--;
		}
		sort(a, a+n);

		long long ret = 0;
		for (int i = 0; i < n; i++) {
			long long diff = a[i] - i;
			if (diff < 0) diff = -diff;
			assert(ret+diff >= ret);
			ret += diff;
		}
		printf("%lld\n", ret);

	}
}
