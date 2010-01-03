#include <cstdio>

int main()
{
	int c[32][32], n, k, s=0;
	for (n = 0; n < 30; n++) {
		c[n][0] = 1; c[n][n+1] = 0;
		for (k = 1; k <= n; k++)
			c[n][k] = c[n-1][k-1] + c[n-1][k];
	}
	scanf("%d", &n);
	for (k = 3; k <= n; k += 2)
		s += c[n][k];
	printf("%d\n", s);
}
