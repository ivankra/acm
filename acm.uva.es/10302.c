#include <stdio.h>

int main()
{
	static long long f[50010];
	static int x;
	register int i;

	for (f[0] = 0, i = 1; i < 50010; i++)
		f[i] = f[i - 1] + (long long)i * (long long)i * (long long)i;

	while (scanf("%d", &x) == 1) 
		printf("%lld\n", f[x]);

	return 0;
}
