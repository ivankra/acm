#include <cstdio>

int main()
{
	double E[1024], L, R;
	int i, j, n;

	while (scanf("%d %lf %lf", &n, &L, &R) == 3 && n) {
		for (E[0]=0, i=1; i<=n; i++)
			for (E[i]=1e99, j=0; j<i; j++)
				E[i] <?= (1+(1-R)*E[j]+(1-L)*E[i-1-j])/(1-L-R);
		printf("%.2f\n", E[n]);
	}

	return 0;
}
