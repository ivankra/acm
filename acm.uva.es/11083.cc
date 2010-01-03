#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;i++)
typedef unsigned long long ull;

#define MAXB 100010
char isprime[MAXB+1];

ull f(ull n, ull d) {
	if (n < d) return 0;
	ull t = n/d;
	ull res = (t-1)*t/2*d + t*(n%d+1);
	return res;
}

int main() {
	REP(i, MAXB) isprime[i] = 1;
	isprime[0] = isprime[1] = 0;
	for (int p = 2; p <= 1000; p++) {
		if (isprime[p])
			for (int q = p*p; q < MAXB; q += p) isprime[q] = 0;
	}

	ull n, b;
	while (scanf("%llu %llu", &n, &b) == 2 && (n != 0 || b != 0)) {
		ull p;
		for (p = b; p > 2; p--)
			if (isprime[p] && (b % p) == 0) break;

		ull res = 0;
		for (ull d = p; d <= n; d *= p)
			res += f(n, d);
		printf("%llu\n", res);
	}
}
