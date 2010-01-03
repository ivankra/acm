#include <cstdio>
#include <cstring>

int main() {
	long long f[128];
	int n;
	scanf("%d", &n);
	memset(f, 0, sizeof(f));
	f[0] = 1;
	for (int c = 1; c <= n; c++)
		for (int k = c; k <= n; k++)
			f[k] += f[k-c];
	printf("%lld\n", f[n]);
}
