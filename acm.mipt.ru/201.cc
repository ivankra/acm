#include <cstdio>
#include <cstring>

int main()
{
	int f[1024], n;

	scanf("%d", &n);

	memset(f, 0, sizeof(f));
	f[0] = 1;

	for (int k = 1; k <= 4; k++)
		for (int r = k; r <= n; r++)
			f[r] += f[r-k];
	printf("%d\n", f[n]);
}
