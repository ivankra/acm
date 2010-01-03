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

int f[600000];

int main() {
	int T;
	scanf("%d", &T);

	memset(f, 0, sizeof(f));
	for (int i = 2; i <= 510000; i++) {
		if (f[i] == 0) {
			for (int j = i; j <= 510000; j += i)
				f[j] += i;

			if (i <= 800) {
				for (int k = i*i; k <= 510000;) {
					for (int j = k; j <= 510000; j += k)
						f[j] += i;
				
					long long t = k * (long long)i;
					if (t > 510000) break;
					k = t;
				}
			}
		}
	}

	for (int n = 2; n <= 510000; n++)
		f[n] = (f[n] == n ? 1 : 1 + f[f[n]]);

	for (int cs = 1; cs <= T; cs++) {
		printf("Case #%d:\n", cs);

		int a, b;
		scanf("%d %d", &a, &b);

		if (a > b) swap(a, b);

		int res = f[a];
		for (; a <= b; a++)
			res >?= f[a];
		printf("%d\n", res);
	}
}
