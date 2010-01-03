#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

long long N, best;

int numDigits(long long x) {
	if (x <= 9) return 1;
	return 1 + numDigits(x/10);
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%lld", &N);

		int lenN = numDigits(N);

		best = N;
		for (int i = 0; i < lenN; i++)
			best *= 10;
		best += N;

		for (int period = 2; period <= 30; period++) {
			for (int baseLen = 1; baseLen <= lenN; baseLen++) {
				if (baseLen*period > lenN+lenN) continue;

				long long t = 1;
				for (int i = 0; i < baseLen; i++)
					t *= 10;

				long long x = 1;
				for (int i = 0; i < period-1; i++)
					x = x * t + 1;

				long long g = __gcd(x, N);
				long long p = N / g;

				long long a = ((t/10)/p) * p;
				while (a < (t/10)) a += p;

				if (a >= t) continue;

				long long z = a * x;
				best <?= z;
//				printf("period=%d baseLen=%d: %lld\n", period, baseLen, z);
			}
		}

		printf("%lld\n", best);
	}
}
