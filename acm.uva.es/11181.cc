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

int N, K;
double p[32], q[32];

int main() {
	for (int cs = 1; scanf("%d %d", &N, &K) == 2 && N > 0; cs++) {
		for (int i = 0; i < N; i++) { scanf("%lf", &p[i]); q[i] = 0; }

		double total = 0.0;

		for (int mask = 0; mask < (1 << N); mask++) {
			int c = 0;
			for (int x = mask; x != 0; x &= (x - 1)) c++;
			if (c != K) continue;

			double pr = 1;
			for (int i = 0; i < N; i++)
				if (mask & (1 << i))
					pr *= p[i];
				else
					pr *= 1.0 - p[i];

			for (int i = 0; i < N; i++)
				if (mask & (1 << i)) q[i] += pr;

			total += pr;
		}

		printf("Case %d:\n", cs);
		for (int i = 0; i < N; i++)
			printf("%.6f\n", K == 0 ? 0.0 : (q[i]/total));
	}
}
