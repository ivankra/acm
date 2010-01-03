#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

int a[1000010], n;

int main()
{
	int T;
	for (scanf("%d", &T); T-- > 0 && scanf("%d", &n) == 1;) {
		assert(1 <= n && n <= 1000000);
		long long sum = 0, asum = 0, maxi = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			if (a[i] == 0) { n--; i--; }
			sum += a[i];
			asum += abs(a[i]);
			maxi >?= abs(a[i]);
		}

//		printf("n=%d sum=%lld asum=%lld maxabs=%lld\n", n, sum, asum, maxi);

// EASY SOLVER
		for (int i = 0; i < n; i++) assert(a[i] > 0);

		long long cnt = 0;
		for (int i = 0; i < n; i++) {
			long long sum = 0;
			for (int j = i; ; j++) {
				if (sum == 47) { cnt++; break; }
				if (sum > 47) break;
				if (j >= n) break;
				sum += a[j];
			}
		}
		printf("%lld\n", cnt);

	}
}
