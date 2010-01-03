#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

double num[4][4][4], den[4][4];

int A[10], cnt;
void gen(int k, int n, int m) {
	if (k < n+m) {
		for (A[k] = 1; A[k] <= 6; A[k]++)
			gen(k+1, n, m);
		return;
	}

	int p[10], q[10];
	for (int i = 0; i < n; i++) p[i] = A[i];
	for (int i = 0; i < m; i++) q[i] = A[n+i];

	sort(p, p+n, greater<int>());
	sort(q, q+m, greater<int>());

	den[n][m]++;

	for (int i = 1; i < n; i++) assert(p[i-1] >= p[i]);
	for (int i = 1; i < m; i++) assert(q[i-1] >= q[i]);

	int x = 0;
	for (int i = 0; i < n && i < m; i++)
		if (p[i] > q[i]) x++;

	num[n][m][x] += 1.0;
}

char got[1800][1010];
double memo[1800][1010];

double f(int n, int m) {
	if (got[n][m] != 0) return memo[n][m];
	got[n][m] = 1;

	double &res = memo[n][m];

	if (n <= 1) return res = 0;
	if (m == 0) return res = 1;

	res = 0;
	for (int a = 1; a <= 3 && a <= n-1; a++) {
		double t = 1e99;
		for (int b = 1; b <= 3 && b <= m; b++) {
			double prob = 0;
			for (int as = 0; as <= a && as <= b; as++) {
				int bs = min(a,b) - as;
				prob += num[a][b][as]/den[a][b] * f(n-bs, m-as);
			}
			t <?= prob;			
		}
		res >?= t;
	}
	return res;
}

int main() {
	for (int n = 1; n <= 3; n++)
	for (int m = 1; m <= 3; m++) {
		for (int k = 0; k < 4; k++) num[n][m][k] = 0;
		den[n][m] = 0;
		gen(0, n,m);
	}

	memset(got, 0, sizeof(got));

#if 1
	int M;
	while (scanf("%d", &M) == 1 && M > 0) {
		for (int N = 1;; N++)
			if (f(N, M) > 0.5+1e-9) { printf("%d\n", N); break; }
	}
#else
	for (int M = 1; M <= 1000; M++) {
		for (int N = 1;; N++)
			if (f(N, M) > 0.5+1e-9) { printf("%d,\n", N); break; }
	}
#endif

	return 0;
}
