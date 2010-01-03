#include <stdio.h>
#include <string.h>

#define M 256

unsigned long long f[M][M];

int main()
{
	memset(f, 0, sizeof(f));

	f[0][0] = 1;

	for (int k = 1; k < M; k++)
		for (int n = 0; n < M; n++) {
			f[k][n] = f[k-1][n];
			if (n >= k) f[k][n] += f[k][n-k];
		}

	for (int n = 0; n < M; n++)
		printf("%5d  %llu\n", n, f[M-1][n]);

	return 0;
}
