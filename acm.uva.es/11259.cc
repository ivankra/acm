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

long long ways[100010];

int main()
{
	int c[4], d[4], v, T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		for (int i = 0; i < 4; i++) {
			scanf("%d", &c[i]);
			if (i > 0) assert(c[i-1] < c[i]);
		}

		for (int n = 0; n <= 100000; n++) ways[n] = 0;
		ways[0] = 1;

		for (int i = 0; i < 4; i++)
			for (int n = c[i]; n <= 100000; n++)
				ways[n] += ways[n - c[i]];

		int Q;
		scanf("%d", &Q);

		for (int q = 1; q <= Q; q++) {
			for (int i = 0; i < 4; i++) scanf("%d", &d[i]);
			scanf("%d", &v);

			long long res = 0;
			for (int mask = 0; mask < 16; mask++) {
				long long n = v, sign = 1;
				for (int i = 0; i < 4; i++) {
					if (mask & (1 << i)) {
						n -= (d[i] + 1) * c[i];
						sign = -sign;
					}
				}
				if (n >= 0) {
					res += sign * ways[n];
				}
			}
			printf("%lld\n", res);
		}
	}
}
