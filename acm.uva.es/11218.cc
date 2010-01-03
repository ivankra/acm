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
typedef long long ll;

int N, a[100], b[100];

int main() {
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		for (int i = 0; i < N; i++) {
			a[i] = b[i] = 0;
			for (int j = 0; j < 3; j++) {
				int k;
				scanf("%d", &k);
				k--;
				a[i] |= 1 << k;
			}
			scanf("%d", &b[i]);
		}

		int best = -1;
		for (int i = 0; i < N; i++) {
			for (int j = i+1; j < N; j++) {
				if ((a[i] & a[j]) != 0) continue;
				for (int k = j+1; k < N; k++) {
					if ((a[i] | a[j] | a[k]) == 511) {
						best >?= b[i] + b[j] + b[k];
					}
				}
			}
		}

		printf("Case %d: %d\n", cs, best);
	}
}
