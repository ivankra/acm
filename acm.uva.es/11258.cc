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

int main()
{
	int T;
	scanf("%d", &T);

	char S[1000];
	long long maxSum[1000];

	for (int cs = 1; cs <= T; cs++) {
		scanf(" %s", S);

		int N = strlen(S);
		maxSum[0] = 0;
		for (int n = 1; n <= N; n++) {
			maxSum[n] = -(1LL << 60);
			for (int k = 1; k <= 10 && k <= n; k++) {
				long long num = 0;
				for (int i = 0; i < k; i++)
					num = num * 10 + S[n-k+i]-'0';

				if (0 <= num && num < (1LL<<31)) {
					maxSum[n] >?= num + maxSum[n-k];
				}
			}
		}

		printf("%lld\n", maxSum[N]);
	}
}
