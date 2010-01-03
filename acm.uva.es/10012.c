#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

vector<double> R;
int n;

double eval()
{
	double x[16], r;
	int i, j;

	x[0] = R[0];
	for (i = 1; i < n; i++) {
		x[i] = max(x[i-1], R[i]);
		for (j = 0; j < i; j++)
			x[i] = max(x[i], x[j] + 2. * sqrt(R[i] * R[j]));
	}

	for (r = x[n-1], i = 0; i < n; i++)
		r = max(r, x[i] + R[i]);

	return r;
}

int main()
{
	int i, t;
	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		R.resize(n);
		for (i = 0; i < n; i++) {
			scanf("%lf", &R[i]);
			if (R[i] < 0.) R[i] = 0.;
		}

		sort(R.begin(), R.end());
		double z = eval();
		while (next_permutation(R.begin(), R.end())) z = min(z, eval());

		printf("%.3f\n", z+1e-12);
	}
	return 0;
}
