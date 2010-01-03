/*
ID: infnty1
PROB: stamps
LANG: C++
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int N, K, U, val[50], f[2000010];

int main() {
	freopen("stamps.in", "r", stdin);
	freopen("stamps.out", "w", stdout);

	scanf("%d %d", &K, &N);
	for (int i = 0; i < N; i++) scanf("%d", &val[i]);

	f[0] = 0;
	for (int i = 1;; i++) {
		f[i] = 1<<30;
		for (int j = 0; j < N; j++)
			if (val[j] <= i) f[i] <?= 1 + f[i - val[j]];

		if (f[i] > K) {
			printf("%d\n", i-1);
			break;
		}
	}
}
