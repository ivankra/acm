#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		long long N;
		scanf("%lld", &N);

		if (N < 1) N = 1;
		N--;

		long long K = N / 3;
		long long res = K*(K+1)/2*3 + (N % 3) * (K + 1);
		printf("%lld\n", res);
	}

/*N=1 => 0 s=0
N=2 => 1 s=0  = 1
N=3 => 2 s=0    11
N=4 => 3 s=1    111
N=5 => 5 s=1    1112
N=6 => 7 s=1    11122
N=7 => 9 s=2    111222
N=8 => 12 s=2   1112223
	
	for (int N = 1; N <= 20; N++) {
		int res = INT_MAX;
		int at = 0;
		for (int s = 0; s <= N; s++) {
			int w = s*(s+1)/2;
			for (int i = s+1; i <= N; i++)
				w += max(0, 2*i - N - (s+1));
			if (w < res) {
				res = w;
				at = s;
			}
		}
		printf("N=%d => %d s=%d\n", N, res, at);
	}*/
}
