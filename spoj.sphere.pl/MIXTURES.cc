// DP, similar to optimal matrix-chain multiplication
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

int color[200], sum[200], n;
int best[200][200];

int main()
{
	while (scanf("%d", &n) == 1 && n > 0) {
		sum[0] = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &color[i]);
			sum[i] = sum[i-1] + color[i];
		}

		for (int a = 1; a <= n; a++)
			best[1][a] = 0;

		for (int len = 2; len <= n; len++) {
			for (int a = 1; a+len-1 <= n; a++) {
				int b = a + len - 1;
				best[len][a] = 1<<30;
				for (int c = a+1; c <= b; c++) {
					int left = (sum[c-1] - sum[a-1]) % 100;
					int right = (sum[b] - sum[c-1]) % 100;
					int t = left * right + best[c-a][a] + best[b+1-c][c];
					best[len][a] = min(best[len][a], t);
				}
			}
		}

		printf("%d\n", best[n][1]);
	}
}
