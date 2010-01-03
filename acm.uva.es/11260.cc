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
typedef unsigned long long ull;

ull MOD = 100000000;

int main()
{
	ull N;
	while (scanf("%llu", &N) == 1 && N != 0) {
		if (N % 2 == 0) N--;

		N = (N + 1) / 2;

		ull left = 0, right = 3000000000LL;
		while (right - left > 1) {
			ull k = (left + right) / 2;
			if (2*k*(k+1) <= N) left = k; else right = k;
		}

		ull K = left;
		ull m[3] = { K, K+1, 2*K+1 };
		for (int i = 0; i < 3; i++)
			if (m[i] % 3 == 0) { m[i] /= 3; break; }

		ull res = m[0] % MOD;
		res = (res * m[1]) % MOD;
		res = (res * m[2]) % MOD;
		res = (res * 4) % MOD;
		res = (res + MOD - ((K*(K+1))%MOD)) % MOD;

		N -= 2*K*(K+1);

		for (int i = 0; i < 2 && N > 0; i++) {
			ull cnt = min(N, 2*(K+1));
			res += cnt * (2*(K+1)-1+i);
			N -= cnt;
			res %= MOD;
		}
		printf("%lld\n", res);

/*
1122
33334444
555555666666
7777777788888888
9999999999 ...  */

	}
}
