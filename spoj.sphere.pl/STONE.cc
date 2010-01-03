#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	static int x[1000001], y[1000001];
	int T, N;
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d %d", &x[i], &y[i]);
		x[N] = x[0];
		y[N] = y[0];

		double cx = 0, cy = 0, area = 0;

		for (int i = 0; i < N; i++) {
			double w = x[i] * y[i+1] - x[i+1] * y[i];
			area += w;
			cx += w * (x[i] + x[i+1]) / 3;
			cy += w * (y[i] + y[i+1]) / 3;
		}

		cx /= area;
		cy /= area;
		if (fabs(cx) < 0.005 - 1e-9) cx = 0;
		if (fabs(cy) < 0.005 - 1e-9) cy = 0;

		printf("%.2f %.2f\n",
				cx + 1e-9 * (cx >= -1e-9 ? 1 : -1),
				cy + 1e-9 * (cy >= -1e-9 ? 1 : -1));
	}
}
