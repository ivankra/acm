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

long long f(long long m, int c)
{
	return (m - 7 + c) / 2;
}

int main() {
	long long n, m, c;
	while (scanf("%lld %lld %lld", &n, &m, &c) == 3 && n > 0) {
		long long res = 0;

		if (n > 50) {
			long long k = n - 20;
			if (k % 2 != 0) k--;
			res += (f(m, 0) + f(m, 1)) * (k / 2);
			n -= k;
		}

		while (n >= 8) {
			res += f(m, c);
			c ^= 1;
			n--;
		}

		printf("%lld\n", res);
	}
}
