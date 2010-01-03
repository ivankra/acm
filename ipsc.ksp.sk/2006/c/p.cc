#include <cstdio>
#include <cassert>
#include <algorithm>
#include <map>
using namespace std;

int a[1000010], n;

int main()
{
	int T;
	for (scanf("%d", &T); T-- > 0 && scanf("%d", &n) == 1;) {
		assert(1 <= n && n <= 1000000);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);

		long long cnt = 0;
		map<long long, long long> M;

		M[0] = 1;
	
		long long sum = 0;
		for (int i = 0; i < n; i++) {
			sum += a[i];
			if (M.count(sum - 47) > 0) cnt += M[sum - 47];

			if (M.count(sum) == 0)
				M[sum] = 1;
			else
				M[sum] = M[sum] + 1;
		}
		printf("%lld\n", cnt);

	}
}
