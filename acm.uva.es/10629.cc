#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

int D, N, MaxTime;

struct Light {
	int x, red, green;

	int t[6000], k;
	double dp[6000];

	bool operator <(const Light &l) const { return x < l.x; }
} light[52];

bool check(int from, int to, int t1_20, int x1, int t2_20, int x2)
{
	assert(x1 < x2);
	for (int i = from; i <= to; i++) {
		const Light &L = light[i];
		int p = t1_20*(x2-x1) + (t2_20-t1_20)*(L.x-x1);
		int q = 20*(x2 - x1);
		p %= q * (L.red + L.green);
		if (0 < p && p < q*L.red) return false;
	}
	return true;
}

double lineCost(double dx, double dt) {
	return dx + dt*dt/dx - 0.1*dt;
}

double solve()
{
	if (D <= 0) return 0;
	if (N == 0) return lineCost(D, D/20.0);

	MaxTime = D/20 + 5;
	for (int i = 1; i <= N; i++)
		MaxTime += light[i].red;
//	printf("maxtime=%d\n", MaxTime);

	for (int i = 1; i <= N; i++) {
		Light &L = light[i];

		assert(0 < L.x && L.x < D);

		L.k = 1;
		L.t[0] = L.red;

		while (true) {
			L.t[L.k] = L.t[L.k-1] + (L.k % 2 == 1 ? L.green : L.red);
			if (L.t[L.k] > MaxTime) break;
			L.k++;
		}
	}

	light[0].k = 1;
	light[0].t[0] = 0;
	light[0].dp[0] = 0;

	for (int b = 1; b <= N; b++) {
		Light &B = light[b];
		for (int bi = 0; bi < B.k; bi++) {
			double res = 1e99;
			for (int a = 0; a < b; a++) {
				const Light &A = light[a];
				for (int ai = 0; ai < A.k && A.t[ai] < B.t[bi]; ai++) {
					if (!check(a+1, b-1, A.t[ai]*20, A.x, B.t[bi]*20, B.x))
						continue;

					double dx = B.x - A.x;
					double dt = B.t[bi] - A.t[ai];
					res = min(res, A.dp[ai] + lineCost(dx, dt));
				}
			}
			B.dp[bi] = res;
//printf("b=%d (x=%d),  bi=%d (t=%d): dp=%.3f\n", b, L[b].x, bi, L[b].t[bi], dp[b][bi]);
		}
	}

	double best = 1e99;
	for (int a = 0; a <= N; a++) {
		const Light &A = light[a];
		for (int ai = 0; ai < A.k; ai++) {
			int x0 = A.x, dx = D - x0;
			int t0_20 = A.t[ai] * 20;
			int t1_20 = t0_20 + dx;
			if (check(a+1, N, t0_20, x0, t1_20, D)) {
				best = min(best, A.dp[ai] + lineCost(dx, dx/20.0));
			}
		}
	}
	return best;
}

int main()
{
	while (cin >> D >> N) {
		if (D == 0 && N == 0) break;

		for (int i = 1; i <= N; i++)
			cin >> light[i].x >> light[i].red >> light[i].green;
		sort(light+1, light+N+1);

		printf("%.2f\n", solve());
	}

}
