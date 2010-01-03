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

long long N, bestA, bestB;

void checkDiv(long long m)
{
	long long sum = (2 * N) / m;

	long long b = sum + m - 1;
	if (b % 2 != 0) return;
	b /= 2;

	long long a = sum - b;
	if (a > b || a < 0) return;
	if (a == 0) a = 1;

	if (m > bestB - bestA + 1) {
		bestA = a;
		bestB = b;
	}
}

int main()
{
	while (scanf("%lld", &N) == 1 && N >= 1) {
		bestA = bestB = N;
		for (long long d = 1; d*d <= (2*N); d++) {
			if ((2*N) % d == 0) { checkDiv(d); checkDiv((2*N)/d); }
		}
		printf("%lld = %lld + ... + %lld\n", N, bestA, bestB);
	}
}
