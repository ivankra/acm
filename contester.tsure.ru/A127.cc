#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

long long pw(long long x, int y, long long m) {
	long long res = 1;
	for (; y > 0; y >>= 1) {
		if (y & 1) res = (res * x) % m;
		x = (x * x) % m;
	}
	return res;
}

int main()
{
	int n;
	scanf("%d", &n);

	int k = 0;
	long long m = 1;
	while (k < 9) {
		m *= 10;

		long long t = 1 + pw(2, n, m) + pw(3, n, m) + pw(4, n, m);
		t %= m;
		if (t != 0) break;

		k++;
	}

	printf("%d\n", k);
}
