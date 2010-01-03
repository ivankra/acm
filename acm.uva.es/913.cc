#include <cstdio>

int main()
{
	long long N;
	while (scanf("%lld", &N) == 1 && N > 0) {
		long long k = (N+1)/2;
		long long z = 2*(k*(k+1)-k)-1;
		printf("%lld\n", z + z-2 + z-4);
	}
}