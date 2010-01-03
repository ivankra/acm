#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

#define MAX 100

double dp[102][102][102];  // n,m,k;  Pr[Jim never draws a short stick]

void doit()
{
	memset(dp, 0, sizeof(dp));

	for (int m = 0; m <= MAX; m++)
		dp[1][m][0] = 1.0;

	for (int n = 2; n <= MAX; n++) {
		for (int m = 0; m <= MAX; m++) {
			// n-1 short straws, m long straws
			for (int k = 0; k < n; k++) {
				// short
				double pS = (n - 1) / (double)(n - 1 + m);
				double pL = 1 - pS;
				if (k != 0) {
					dp[n][m][k] += pS * dp[n-1][m][k-1];
				}

				// long
				if (m > 0) {
					if (k == 0) {
						dp[n][m][k] += pL * dp[n][m-1][n-1];
					} else {
						dp[n][m][k] += pL * dp[n][m-1][k-1];
					}
				}
			}
		}
	}
}

int main()
{
	int T, n, m, k;
	doit();
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d", &n, &m, &k);
		printf("%.3f\n", dp[n][m][k] * 100.0);
	}
}
