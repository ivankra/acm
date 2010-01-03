#include <cstdio>
#include <cstring>

int main() {
	long long a[120]={0,1,1,1};
	int n;

	for (n = 3; n <= 100; n++)
		a[n] = a[n-2] + a[n-3];

	while (scanf("%d", &n) == 1)
		printf("%lld\n", (n >= 2 ? a[n]+a[n-1] : 1));
}
