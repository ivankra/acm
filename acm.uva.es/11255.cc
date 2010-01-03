#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
typedef unsigned long long ull;

ull cache[42][42][42];
ull dp[42][42][42];
int cyc[50], ncyc;

void compute(int N)
{
	int pi[50];

	for (int rot = 0; rot < N; rot++) {
		for (int flip = 0; flip < 2; flip++) {
			// generate permutation
			for (int i = 0; i < N; i++) pi[i] = (i + rot) % N;
			if (flip) {
				for (int i = 0, j = N-1; i < j; i++, j--)
					swap(pi[i], pi[j]);
			}

			// compute lengths of cycles
			ncyc = 0;
			for (int i = 0; i < N; i++) {
				if (pi[i] < 0) continue;
				int c = 0;
				for (int x = i; pi[x] != -1;) {
					int y = pi[x];
					pi[x] = -1;
					x = y;
					c++;
				}
				cyc[ncyc++] = c;
			}

			sort(cyc, cyc+ncyc);

			for (int a = 0; a <= N; a++)
				for (int b = 0; b <= N; b++)
					for (int c = 0; c <= N; c++)
						dp[a][b][c] = 0;

			dp[0][0][0] = 1;

			int s = 0;
			for (int i = 0; i < ncyc; i++) {
				s += cyc[i];
				for (int a = 0; a <= s; a++) {
					for (int b = 0; a+b <= s; b++) {
						int c = s-a-b;
						if (a >= cyc[i]) dp[a][b][c] += dp[a-cyc[i]][b][c];
						if (b >= cyc[i]) dp[a][b][c] += dp[a][b-cyc[i]][c];
						if (c >= cyc[i]) dp[a][b][c] += dp[a][b][c-cyc[i]];
					}
				}
			}

			for (int a = 0; a <= N; a++) {
				for (int b = 0; a+b <= N; b++) {
					int c = N-a-b;
					cache[a][b][c] += dp[a][b][c];
				}
			}

		}
	}

	for (int a = 0; a <= N; a++) {
		for (int b = 0; a+b <= N; b++) {
			int c = N-a-b;
			cache[a][b][c] /= 2*N;
		}
	}
}

int main()
{
	int T, a[3];
	scanf("%d", &T);
	memset(cache, 0, sizeof(cache));
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d", &a[0], &a[1], &a[2]);
		sort(a, a+3);
		ull &res = cache[a[0]][a[1]][a[2]];
		if (res == 0) compute(a[0] + a[1] + a[2]);
		printf("%llu\n", res);
	}
}
