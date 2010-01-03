/*
ID: infnty1
PROB: cowcycle
LANG: C++
*/
#include <cstdio>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

int F, R, flo, fhi, rlo, rhi;
int bestF[100], bestR[100], curF[100], curR[100];
double bestVar;

void check() {
	static double z[1000];
	int m = 0;

	for (int i = 0; i < F; i++)
		for (int j = R-1; j >= 0; j--)
			z[m++] = curF[i] / (double)curR[j];
	sort(z, z+m);

	double mean = (z[m-1] - z[0]) / (m - 1);

	double var = 0;
	for (int i = 1; i < m; i++) {
		double t = z[i] - z[i-1];
		var += (t - mean) * (t - mean);
		if (var >= bestVar) return;
	}

	bestVar = var;
	memcpy(bestF, curF, F*sizeof(int));
	memcpy(bestR, curR, R*sizeof(int));
}

void try_r(int k, int x) {
	if (k >= R-1) {
		check();
	} else {
		while (x < rhi) {
			curR[k] = x++;
			try_r(k+1, x);
		}
	}
}

void try_f(int k, int x) {
	if (k >= F-1) {
		try_r(1, rlo+1);
	} else {
		while (x < fhi) {
			curF[k] = x++;
			try_f(k+1, x);
		}
	}
}

int main()
{
	freopen("cowcycle.in", "r", stdin);
	freopen("cowcycle.out", "w", stdout);

	int F1, F2, R1, R2;
	scanf("%d %d %d %d %d %d", &F, &R, &F1, &F2, &R1, &R2);
	assert(F > 1 || R > 1);

	bestVar = 1e99;

	for (flo = F1; flo <= F2; flo++)
	for (fhi = flo; fhi <= F2; fhi++)
	for (rlo = R1; rlo <= R2; rlo++)
	for (rhi = rlo; rhi <= R2; rhi++) {
		if (F > 1 && fhi <= flo) continue;
		if (R > 1 && rhi <= rlo) continue;

		if (fhi*rhi < 3*flo*rlo) continue;

		curF[0] = flo;
		curF[F-1] = fhi;

		curR[0] = rlo;
		curR[R-1] = rhi;

		try_f(1, flo+1);
	}

	for (int i = 0; i < F; i++) printf(i?" %d":"%d", bestF[i]); printf("\n");
	for (int i = 0; i < R; i++) printf(i?" %d":"%d", bestR[i]); printf("\n");

	return 0;
}
