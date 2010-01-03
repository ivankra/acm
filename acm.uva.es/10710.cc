#include <cstdio>

long long modpow(long long base, long long e, long long mod)
{
	long long res = 1;
	base %= mod;
	while (e > 0) {
		if (e & 1)
			res = (res * base) % mod;
		e >>= 1;
		base = (base * base) % mod;
	}
	return res;
}

bool check(long long N)
{
	return modpow(2, N-1, N) == N % 2;
}

int main()
{
	long long N;
	while (scanf("%lld", &N) == 1 && N >= 2) {
		if (check(N))
			printf("%lld is a Jimmy-number\n", N);
		else
			printf("%lld is not a Jimmy-number\n", N);
	}
}
