#include <stdio.h>
#include <math.h>

unsigned long long seed;

long double gen()
{
    static const long double Z = (long double)1.0 / (1LL<<32);
    seed >>= 16;
    seed &= 0xFFFFFFFFLL;
    seed *= seed;
  /*  printf("%20llX",seed); printf(" %.30Lf\n", (long double)(seed * Z));
*/
    return seed * Z;
}

int main()
{
	int i, n, c, t;
	unsigned long long s;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d %llu", &n, &s) == 2; c++) {
		printf("\nn=%d s=%llX (%lld)\n", n, s, s);
		seed = s;
		for (i = 0; i < n; i++) {
			gen();
			if (seed == 0) { printf("seed=0 at %d\n", i); break; }
		}
	}

	return 0;
}
