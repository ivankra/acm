#include <cstdio>
#include <cstring>

int main()
{
	int f[2048], N;
	scanf("%d", &N);

	memset(f, 0, sizeof(f));
	f[0] = 1;
	for (int k = 1; k <= 4; k++)
		for (int n = k; n <= N; n++)
			f[n] += f[n-k];
	printf("%d\n", f[N]);
}
