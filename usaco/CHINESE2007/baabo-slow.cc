/*
ID: infnty1
LANG: C++
TASK: sumsums
*/
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
#define foreach(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

const long long NINF = -(1LL << 61);

static inline long long sqr(long long x) { return x * x; }

struct Fun {
	long long m[1001], b[1001], N;

	Fun() { N = 0; }

	void clear() { N = 0; }

	// 0<=m<=2*10^6,  |b| <= 10^9
	void add(long long mi, long long bi) {
		m[N] = mi;
		b[N] = bi;
		N++;
	}

	// 0 <= x <= 10^6
	long long eval(int x) {
		long long res = NINF;
		assert(N > 0);
		for (int i = 0; i < N; i++)
			res = max(res, m[i] * x + b[i]);
		return res;
	}
};

int main()
{
	static int N, A[1024], B[1024];
	static long long SA[1024], SB[1024];
	static long long f00[1024][1024], f10[1024][1024], f11[1024][1024];
	static Fun m00[1001], m10;
printf("started %d\n", sizeof(m00) + sizeof(f00)*3);
	freopen("baabo.in", "r", stdin);
//	freopen("baabo.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", &A[i]);
	for (int i = 0; i < N; i++) scanf("%d", &B[i]);

	SA[0] = 0;
	for (int i = 1; i <= N; i++) SA[i] = SA[i-1] + A[i-1];

	SB[0] = 0;
	for (int i = 1; i <= N; i++) SB[i] = SB[i-1] + B[i-1];

	for (int i = 0; i <= N; i++) {
		f00[i][N] = -sqr(SA[N] - SA[i]);
		f00[N][i] = -sqr(SB[N] - SB[i]);
	}

	for (int j = 0; j < N; j++) {
		m00[j].add(SA[N], -sqr(SA[N]));
	}

	for (int i = N-1; i >= 0; i--) {
		m10.clear();
		m10.add(SB[N], -sqr(SB[N]));
		for (int j = N-1; j >= 0; j--) {
			f11[i][j] = A[i] * B[j] + f00[i+1][j+1];

			f10[i][j] = NINF;
			for (int k = j; k <= N; k++)
				f10[i][j] >?= f11[i][k] - sqr(SB[k] - SB[j]);

//			m10.add(SB[j], f11[i][j] - sqr(SB[j]));
//			f10[i][j] = m10.eval(2*SB[j]) - sqr(SB[j]);

			f00[i][j] = NINF;
			for (int k = i; k <= N; k++)
				f00[i][j] >?= f10[k][j] - sqr(SA[k] - SA[i]);

//			m00[j].add(SA[i], f10[i][j] - sqr(SA[i]));
//			f00[i][j] = m00[j].eval(2*SA[i]) - sqr(SA[i]);
		}
	}

	printf("%lld\n", f00[0][0]);

	return 0;
}
