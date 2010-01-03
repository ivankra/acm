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

int x[1024], y[1024], xs[1024], ys[1024], N, M;
int best[1024][1024];

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &N, &M);
		N--;
		M--;

		for (int i = 0; i < N; i++) scanf("%d", &x[i]);
		sort(x, x+N);
		xs[0] = 0;
		for (int i = 1; i <= N; i++) xs[i] = xs[i-1] + x[i-1];

		for (int i = 0; i < M; i++) scanf("%d", &y[i]);
		sort(y, y+M);
		ys[0] = 0;
		for (int i = 1; i <= M; i++) ys[i] = ys[i-1] + y[i-1];

		for (int i = N; i >= 0; i--) {
			for (int j = M; j >= 0; j--) {
				if (i == N && j == M) {
					best[i][j] = xs[N] + ys[M];
					continue;
				}

				best[i][j] = 1<<30;
				if (i < N)
					best[i][j] = min(best[i][j], ys[j] + best[i+1][j]);

				if (j < M)
					best[i][j] = min(best[i][j], xs[i] + best[i][j+1]);
			}
		}

		printf("%d\n", best[0][0]);
	}
}
