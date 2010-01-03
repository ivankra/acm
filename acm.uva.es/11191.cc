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

long long cnt[2048], N, Z;

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%lld", &N) == 1; cs++) {
		memset(cnt, 0, sizeof(cnt));
		Z = 0;

		for (int i = 0; i < N; i++) {
			long long x;
			scanf("%lld", &x);

			if (x == 0) {
				Z++;
			} else {
				static const int primes[10] = {
					2, 3, 5, 7, 11, 13, 17, 19, 23, 29
				};

				int mask = 0;
				if (x < 0) { x = -x; mask ^= 1 << 10; }

				for (int i = 0; i < 10; i++) {
					while (x % primes[i] == 0) {
						x /= primes[i];
						mask ^= 1 << i;
					}
				}
				cnt[mask]++;
			}
		}

		long long X = 0;
		for (int i = 0; i < 2048; i++)
			X += cnt[i] * (cnt[i] - 1) / 2;
		X += Z * (N - Z);
		X += Z * (Z - 1) / 2;

		long long Y = 0;
		for (int i = 0; i < 2048; i++) {
			if (cnt[i] == 0) continue;
			for (int j = i; j < 2048; j++) {
				int k = i ^ j;
				if (k < i || k < j) continue;

				if (i == j && j == k)
					Y += cnt[i] * (cnt[i]-1) * (cnt[i]-2) / 6;
				else if (i == j)
					Y += cnt[i] * (cnt[i]-1) / 2 * cnt[k];
				else if (i == k)
					Y += cnt[i] * (cnt[i]-1) / 2 * cnt[j];
				else if (j == k)
					Y += cnt[j] * (cnt[j]-1) / 2 * cnt[i];
				else
					Y += cnt[i] * cnt[j] * cnt[k];
			}
		}
		Y += (N-Z)*(N-Z-1)/2 * Z;
		Y += Z*(Z-1)/2 * (N-Z);
		Y += Z*(Z-1)/2 * (Z-2)/3;

		printf("%lld %lld\n", X, Y);
	}
}
