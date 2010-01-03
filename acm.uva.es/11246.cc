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

int main()
{
	int T;
	scanf("%d", &T);

	long long n, k;
	for (int cs = 1; cs <= T && scanf("%lld %lld", &n, &k) == 2; cs++) {
		long long res = 0;
		for (int level = 0; n > 0; level++) {
			// promote multiplies of k among 1..n to the next level
			long long next = n / k;
			long long cur = n - next;
			if (level % 2 == 0) res += cur;
			n = next;
		}
		printf("%lld\n", res);
	}
}
