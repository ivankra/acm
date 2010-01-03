#include <stdio.h>

int main()
{
	int f[64], s, i, k;
	scanf("%d", &k);
	for (f[1] = f[2] = 1, i = 3; i <= k; i++) f[i] = f[i-1] + f[i-2];
	for (s = 0, i = 1; i <= k; i++) s += f[i];
	printf("%d\n", s);
	return 0;
}
