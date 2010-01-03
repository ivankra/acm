#include <stdio.h>

int main()
{
	static int n;
	static long long r;

	while (scanf("%d", &n) == 1 && n >= 0) {
		r = 1 + (((long long)n * (long long)(n + 1)) >> 1);
		printf("%lld\n", r);
	}

	return 0;
}
