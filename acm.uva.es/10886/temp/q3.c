#include <stdio.h>
#include <math.h>

unsigned long long seed;

long double gen()
{
    static const long double Z = (long double)1.0 / (1LL<<32);
    seed >>= 16;
    seed &= 0xFFFFFFFFLL;
    seed *= seed;
    return seed * Z;
}

int main()
{
	int i, n, c, t;
	unsigned long long s, prev;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d %llu", &n, &s) == 2; c++) {
		printf("\nn=%d s=%llX (%lld)\n", n, s, s);
		seed = s;
		prev = s + 1;
		for (i = 0; i < n; i++) {
			gen();
			if (seed == prev) {
				printf("seed converged to %llX at %d\n", seed, i);
				break;
			}
			prev = seed;
		}
	}

	return 0;
}
