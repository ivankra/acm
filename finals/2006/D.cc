#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int num[20][100010], rev[20][100010], a[100010], M, INF=999999;

int main() {
	while (scanf("%d", &M) == 1 && M > 0) {
		for (int s = -9; s <= 9; s++) {
			for (int n = 0; n < M; n++)
				rev[10+s][n] = INF;

			num[10+s][0] = 0;
			for (int n = 1; n <= M; n++) {
				num[10+s][n] = (((num[10+s][n-1] * 10 + s) % M) + M) % M;
				rev[10+s][num[10+s][n]] <?= n;
			}
		}

		for (int N = 2; ; N++) {
			for (int s = 1; s <= 9; s++) {
				for (int t = 0; t <= 9; t++) {
					if (s == t) continue;
					if (rev[10+s-t][num[10+s][N]] >= N) continue;

					int dir = (s > t ? -1 : 1), m;
					for (m = (dir > 0 ? 1 : N-1); 1 <= m && m <= N-1; m += dir) {
						if (num[10+s][N] == num[10+s-t][m]) break;
					}

					if (N <= 5) {
						int x = 0;
						for (int i = 0; i < N-m; i++) x = x * 10 + s;
						for (int i = 0; i < m; i++) x = x * 10 + t;
						if (x <= M) continue;
					}

					printf("%d: %d %d %d %d\n", M, N-m, s, m, t);
					goto done;
				}
			}
		}

done:;
	}
}
