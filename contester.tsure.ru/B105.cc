#include <cstdio>

int main()
{
	unsigned long long f[64]={1,1};
	for (int i = 2; i < 64; i++) f[i]=f[i-1]+f[i-2];
	int n;
	scanf("%d", &n);
	printf("%llu\n", f[n]);
}
