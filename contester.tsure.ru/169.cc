#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	int n;
	cin >> n;

	double x[100], y[100], r[100];
	for (int i = 0; i < n; i++)
		cin >> x[i] >> y[i] >> r[i];

	int m = 1000, res = 0;
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= m; j++) {
			double x0 = i / (double)m;
			double y0 = j / (double)m;

			for (int k = 0; k < n; k++) {
				if ((x[k]-x0)*(x[k]-x0)+(y[k]-y0)*(y[k]-y0) < r[k]*r[k]+1e-9) {
					res++;
					break;
				}
			}
		}
	}

	printf("%.6f\n", res*100.0/(m*m));
}
