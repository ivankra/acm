/*
ID: infnty1
PROB: job
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m[2], mach[2][100], T[2], P[2][20010];

int main()
{
	freopen("job.in", "r", stdin);
	freopen("job.out", "w", stdout);

	scanf("%d %d %d", &n, &m[0], &m[1]);
	memset(P, 0, sizeof(P));
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < m[k]; i++)
			scanf("%d", &mach[k][i]);

		sort(mach[k], mach[k]+m[k]);
//		if (k == 1) reverse(mach[k], mach[k]+m[k]);

		for (T[k] = 0;; T[k]++) {
			int maxn = 0;
			for (int i = 0; i < m[k]; i++)
				maxn += T[k] / mach[k][i];
			if (maxn >= n) break;
		}

		for (int i = 0; i < m[k]; i++) {
			int z = mach[k][i];
			for (int t = z; t <= T[k]; t += z)
				P[k][t]++;
		}

		for (int t = 1; t <= T[k]; t++)
			P[k][t] += P[k][t-1];

/*		printf("T[%d] = %d\n", k, T[k]);
		for (int t = 0; t <= T[k]; t++)
			printf("%3d", t);
		printf("\n");
		for (int t = 0; t <= T[k]; t++)
			printf("%3d", P[k][t]);
		printf("\n\n");

		for (int t = T[k]; t >= 0; t--)
			printf("%3d", t);
		printf("\n");
		for (int t = T[k]; t >= 0; t--)
			printf("%3d", P[k][t]);
		printf("\n");
*/
	}

	for (int shift = 1;; shift++) {
		for (int t1 = 0; ; t1++) {
			if (t1 > T[1]) {
				printf("%d %d\n", T[0], shift+T[1]);
				return 0;
			}

			int t0 = T[1] - t1 + shift - 1;
			int n0 = (t0 > T[0] ? n : P[0][t0]);
			if (n - P[1][t1] > n0) break;
		}
	}
}
