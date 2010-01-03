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

/*
xxxxaaaabbbbxxxx
    mmmmmmmm

mid = (s >> 16) & 0xFFFFFFFF

seed < 2^16, mid=0,
mid' = mid^2 >> 16
mid*mid < 2^16, mid' < 256...

lower and upper 16 bits of the seed are irrelevant
if seed < 2^32, the seed converges to 0
if seed == 2^32 the seed converges to 2^32, gen -> 1

mid' << 16 = mid * mid  & 0xffffffff

seed = a << 16
65536 a = a a  (mod 0xffffffff)

a (a - 65536) = 0 (mod 0xffffffff)


a=0
a=10000
a=1008020
a=2008010
a=4008008
a=8008004
a=10008002
a=20008001
a=AAAA5555

*/


/*
z = 2^-32

seed =  (seed >> 16) & 0xFFFFFFFF

*/

long double solve(int n, unsigned long long s)
{
	long double m, d, t;
	int i;

	seed = s;

	for (m = 0, i = 0; i < n; i++)
		m += gen() / (long double)n;
printf("(m=%.5Lf) ", m);
fflush(stdout);

	seed = s;
	for (d = 0, i = 0; i < n; i++) {
		t = gen() - m;
		d += t * t / (long double)n;
	}
printf("(d=%.5Lf) ",d);

	return (long double)sqrt(d);
}

int main()
{
	int n, c, t;
	unsigned long long s;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d %llu", &n, &s) == 2; c++)
		printf("Case #%d: %.5Lf\n", c, solve(n, s));

	return 0;
}
