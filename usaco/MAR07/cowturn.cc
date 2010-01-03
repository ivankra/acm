/*
ID: infnty1
LANG: C++
TASK: cowturn
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

int a[5010], N, K;
int INF = 1<<30;

int solve() {
	int M = 0, x[5010], Xor = 0;
	for (int i = 0; i < N; i++) x[i] = 0;

	for (int i = 0; i < N; i++) {
		Xor ^= x[i];
		if ((a[i] ^ Xor) != 0) {
			if (i+K > N) return INF;
			Xor ^= 1;
			x[i+K] ^= 1;
			M++;
		}
	}

	return M;
}

int main() {
	freopen("cowturn.in", "r", stdin);
	freopen("cowturn.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		char ch;
		scanf(" %c", &ch);
		a[i] = (ch == 'F' ? 0 : 1);
	}

	int bestK = 1, bestM = INF;
	for (K = 1; K <= N; K++) {
		int M = solve();
		if (M < bestM) {
			bestK = K;
			bestM = M;
		}
	}
	printf("%d %d\n", bestK, bestM);
}
