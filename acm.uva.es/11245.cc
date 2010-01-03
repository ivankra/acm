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
typedef long long LL;

LL num[1000], len[1000], sum[1000];
int p;

/* difference sequence:
	if (k > 0) {
		for (int i = k-1; i >= 0; i--) {
			for (int j = 0; j < p-2; j++)
				rec(i);
		}
	}
	printf("%lld ", num[k]);
*/

LL getSum(int k, LL n) {
	assert(0 <= n && n <= len[k]);
	if (n == 0) return 0;
	if (n == len[k]) return sum[k];

	LL s = 0;
	for (int i = k-1; i >= 0; i--) {
		if (n <= (p-2) * len[i])
			return s + (n/len[i])*sum[i] + getSum(i, n%len[i]);
		s += (p-2)*sum[i];
		n -= (p-2)*len[i];
	}

	assert(false);
	return 42;
}

int main()
{
	long long n;
	int T, k;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%lld %d", &n, &p);

		num[0] = len[0] = sum[0] = 1;
		for (k = 1; k < 100; k++) {
			num[k] = (num[k-1] - 1) * p + 2;
			len[k] = 1;
			sum[k] = num[k];
			for (int i = k-1; i >= 0; i--) {
				len[k] += (p - 2) * len[i];
				sum[k] += (p - 2) * sum[i];
			}
			if (k > 3 && len[k] > n+10) break;
		}

		printf("%lld\n", 1 + getSum(k, n-1));
	}
}
