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
typedef long long LL;

#define MAXN 200010

LL phi[MAXN], phiSum[MAXN];
bool isPrime[MAXN];

int main()
{
	memset(phi, 0, sizeof(phi));

	for (LL p = 2; p < MAXN; p++) {
		if (phi[p] != 0) continue;

		phi[p] = p - 1;
		for (LL q = p+p; q < MAXN; q += p) {
			if (phi[q] == 0) {
				phi[q] = 1;
			}
			phi[q] *= p - 1;
		}

		for (LL q = p*p; q < MAXN; q *= p) {
			for (LL r = q; r < MAXN; r += q) {
				phi[r] *= p;
			}
		}
	}

	phi[0] = 1;
	phi[1] = 1;

	phiSum[0] = phi[0];
	for (int n = 1; n < MAXN; n++) {
		phiSum[n] = phi[n] + phiSum[n-1];
	}

	LL k;
	while (scanf("%lld", &k) == 1 && k != 0) {
		if (k == 1) { printf("0/1\n"); continue; }

		LL left = 0, right = MAXN-1;
		while (right - left > 1) {
			LL mid = (left + right) / 2;
			if (phiSum[mid] >= k) {
				right = mid;
			} else {
				left = mid;
			}
		}

		int num;
		int d = (int)right;
		k -= phiSum[d - 1];
		for (num = 1; ; num++) {
			if (__gcd(num, d) == 1) {
				if (k <= 1) break;
				k--;
			}
		}
		printf("%d/%d\n", num, d);
	}


}
