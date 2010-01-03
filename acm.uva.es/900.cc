#include <cstdio>

int main()
{
	long long f[100] = { 1, 1 };
	int n;

	for (n = 2; n < 100; n++)
		f[n] = f[n-1] + f[n-2];

	while (scanf("%d", &n) == 1 && n > 0)
		printf("%lld\n", f[n]);
}