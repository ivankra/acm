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
#include <queue>
using namespace std;

int main()
{
	int T;
	scanf("%d", &T);

	vector<int> v;
	for (int n = 0; n <= 999; n++)
		if (n*n*n % 1000 == 888) v.push_back(n);

	long long K;
	for (int cs = 1; cs <= T && scanf("%lld", &K) == 1; cs++) {
		K--;
		long long x = 1000LL * (K / v.size()) + v[K % v.size()];
		printf("%lld\n", x);
	}
}
