#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
	double E[1024], L, R;
	int i, j, k, n;

	while (scanf("%d %lf %lf", &n, &L, &R) == 3 && n) {
		double c0=1/(1-L-R), c1=(1-R)/(1-L-R), c2=(1-L)/(1-L-R);
		if (c1 > c2) swap(c1, c2);
		for (E[0]=0, i=1, k=0; i <= n; i++) {
			E[i] = 1e99;
			for (j = k; j < i; j++) {
				double t = c0 + c1*E[j] + c2*E[i-1-j];
				if (t < E[i]) { E[i]=t; k=j; } else break;
			}
		}
		printf("%.2f\n", E[n]);
	}

	return 0;
}
