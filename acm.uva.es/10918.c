#include <stdio.h>

int main()
{
	int f[32], g[32], n;

	f[0] = 1; f[1] = 0;
	g[0] = 0; g[1] = 1;

	for (n = 2; n <= 30; n++) {
		f[n] = f[n - 2] + 2 * g[n - 1];
		g[n] = f[n - 1] + g[n - 2];
	}

	while (scanf("%d", &n) == 1 && n >= 0)
		printf("%d\n", f[n]);

	return 0;
}
