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

long long m, x;

int compareLL(long long a, long long b) {
	if (a == b) return 0;
	return a > b ? 1 : -1;
}

int compare(long long v1, long long v2) {
	v1 = (v1 < m) ? (v1 * 100) : (v1 * (100 - x));
	v2 = (v2 < m) ? (v2 * 100) : (v2 * (100 - x));
	return compareLL(v1, v2);
}

bool tooHigh(long long v) {
	if (compare(v, m-1) >= 0) return true;
	return false;
}

int main()
{
	while (scanf("%lld %lld", &m, &x) == 2) {
		if (m == 0 && x == 0) break;

		if (x == 0 || x == 100) {
			printf("Not found\n");
			continue;
		}

		long long a = m, b = 100000*m;
		while (b - a > 1) {
			long long mid = (a + b) / 2;
			if (tooHigh(mid))
				b = mid;
			else
				a = mid;
		}

		a += 10;
		while (a >= m && tooHigh(a)) a--;

		if (a < m)
			printf("Not found\n");
		else
			printf("%lld\n", a);
	}
}
