#include <cstdio>
#include <cstring>
#include <cassert>
#include <gmp.h>
using namespace std;

typedef unsigned long long u64;

int isprime(u64 x) {
	if (x <= 2) return (x == 2);
	if ((x & 1) == 0) return 0;

	char s[32];
	sprintf(s, "%llu", x);

	mpz_t a;
	mpz_init_set_str(a, s, 10);
	int r = mpz_probab_prime_p(a, 10);
	mpz_clear(a);

	return r!=0;
}

int main() {
	int T, N;
	u64 a[1010], K;

	for (scanf("%d", &T); T-- > 0;) {
		scanf("%d %llu", &N, &K);
		assert(N < 1000);
		fprintf(stderr, "N=%d K=%llu\n", N, K);
		for (int i = 0; i < N; i++) {
			u64 z;
			scanf("%llu", &z);
			a[i] = 0;
			while (a[i]==0 || (z > 0 && !isprime(z))) {
				z--; a[i]++;
			}

			a[i] %= K+1;
		}

		u64 x = 0;
		for (int i = 0; i < N; i++) x ^= a[i];

		printf((x==0)?"NO\n":"YES\n");
	}
}
