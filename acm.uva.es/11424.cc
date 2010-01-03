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
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long LL;
#define FOREACH(it, v) for(typeof((v).begin())it=(v).begin();it!=(v).end();++it)
#define SIZE(v) ((int)(v).size())
#define ALL(v) (v).begin(), (v).end()
#define REP(i,n) for(int i=0;i<(n);++i)

#define MAXI 200010
char notprime[MAXI];
int phi[MAXI];
long long ans1[MAXI];

int main()
{
	for (int i = 1; i <= MAXI; i++) phi[i] = 1;

	for (int p = 2; p <= MAXI; p++) {
		if (notprime[p]) continue;
		phi[p] = p - 1;

		for (long long q = p; q <= MAXI; q *= p) {
			int qq = (int)q, pp = (q == p ? (p-1) : p);
			for (int j = qq; j <= MAXI; j += qq) {
				notprime[j] = 1;
				phi[j] *= pp;
			}
			if (p > 2100) break;
		}
		phi[p] = p - 1;
	}

	ans1[0] = 0;
	ans1[1] = 0;
	for (int n = 2; n <= MAXI; n++) {
		ans1[n] = ans1[n-1] + phi[n];
	}

	int N;
	while (scanf("%d", &N) == 1 && N > 0) {
		long long res = 0;
		for (int g = 1; g <= N; ) {
			int Ng = N / g;

			/*int left = g, right = N+1;
			while (right - left > 1) {
				int mid = (left + right) / 2;
				if (N/mid == Ng)
					left = mid;
				else
					right = mid;
			}
			int gg = left;*/

			int gg = N/Ng;
			res += (gg-g+1)*(long long)(g+gg)/2 * ans1[Ng];
			g = gg + 1;
		}
		printf("%lld\n", res);
	}
}
