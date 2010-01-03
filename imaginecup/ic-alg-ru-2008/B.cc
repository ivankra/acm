#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
#define SIZE(x) int((x).size())
#define FOREACH(it, x) for(__typeof((x).begin())it=(x).begin();it!=(x).end();++it)
typedef long long LL;
typedef vector<int> VI;

#define SHIFT 3100
#define MAX 6300
#define INF 0x1fffffff

int N, H[2005];
int dp[2005][MAX];

int main()
{
	cin >> N;
	for (int i = 0; i <= N; i++) {
		cin >> H[i];
		H[i] += SHIFT;
	}

	for (int h = 0; h < MAX; h++)
		dp[N][h] = (h == H[N] ? 0 : INF);

	for (int i = N-1; i >= 0; --i) {
		for (int h = 0; h < MAX; h++) {
			dp[i][h] = INF;
			for (int d = -1; d <= 1; d++) {
				if (0 <= h + d && h + d < MAX) {
					dp[i][h] = min(dp[i][h], abs(h - H[i]) + dp[i+1][h+d]);
				}
			}
		}
	}

	printf("%d\n", dp[0][H[0]]);

	for (int i = 0, h = H[0]; ; i++) {
		printf(i == 0 ? "%d" : " %d", h - SHIFT);
		if (i >= N) break;
		for (int d = -1; d <= 1; d++) {
			if (0 <= h + d && h + d < MAX) {
				if (dp[i][h] == abs(h - H[i]) + dp[i+1][h+d]) {
					h += d;
					break;
				}
			}
		}
	}
	printf("\n");


}
