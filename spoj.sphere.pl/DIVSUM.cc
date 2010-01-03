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

int main()
{
	int T, N;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);


		int n = N;
		long long res = 1;

		for (int p = 2; p * p <= n; p++) {
			if (n % p != 0) continue;

			int q = p;
			while (n % p == 0) {
				n /= p;
				q *= p;
			}

			res = res * (q - 1) / (p - 1);
		}

		if (n > 1)
			res *= n + 1;

		printf("%lld\n", res - N);
	}
}
