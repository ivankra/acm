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

long long sum(long long a, long long b) { return (a+b)*(b-a+1)/2; }
long long sum_sq(long long n) { return n*(n+1)*(2*n+1)/6; }
long long sum_sq(long long a, long long b) { return sum_sq(b) - sum_sq(a-1); }

long long f(long long N, long long t) {
	long long res = 0;

	//for (int k = 1; k <= N; k++) res += (N+1-k)*(k/t); return res;

	if (t <= 1000) {
		for (int r = 0; r < t; r++) {
			long long low = (1-r+t-1)/t;
			long long high = (N-r)/t;
			res += (N+1-r)*sum(low, high);
			res -= t*sum_sq(low, high);
		}
	} else {
		int k;
		for (k = t; k+t-1 <= N; k += t)
			res += (t*(N+1) - sum(k, k+t-1)) * (k/t);

		if (k <= N)
			res += ((N+1-k)*(N+1) - sum(k, N)) * (k/t);
	}
	return res;
}

long long g(long long N, long long p) {
	long long res = 0;
	for (long long t = p; t <= N; t *= p)
		res += f(N, t);
	return res;
}

int main() {
	int N, B;
	for (int cs = 1; scanf("%d %d", &N, &B) == 2 && N > 0; cs++) {
		long long res = 1LL<<60;

		for (int p = 2; p*p <= B; p++) {
			if (B % p != 0) continue;

			int m = 0;
			while (B % p == 0) { B /= p; m++; }

			res <?= g(N, p) / m;
		}
		if (B > 1) res <?= g(N, B);

		printf("%lld\n", res);
	}
}
