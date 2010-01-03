#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
using namespace std;
typedef vector<int> VI;  typedef vector<VI> VVI;
typedef long long i64;  typedef unsigned long long u64;

int main() {
	int N;
	i64 a[64];

	for (int cs = 1; scanf("%d", &N) == 1; cs++) {
		for (int i = 0; i < N; i++) scanf("%lld", &a[i]);

		i64 best = 0;

		for (int i = 0; i < N; i++) {
			i64 p = 1;
			for (int j = i; j < N; j++) {
				p *= a[j];
				best >?= p;
			}
		}

		printf("Case #%d: The maximum product is %lld.\n\n", cs, best);
	}

	return 0;
}
