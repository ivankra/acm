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
	int r = mpz_probab_prime_p(a, 50);
	mpz_clear(a);

	return r!=0;
}

#define STDERR stderr
int main() {
	int T, N;
	u64 a[1010], K, x;

	for (scanf("%d", &T); T-- > 0;) {
		scanf("%d %llu", &N, &K);
		assert(N < 1000);
		fprintf(STDERR, "N=%d K=%llu\n", N, K);
int yes=0;
		for (int i = 0; i < N; i++) {
			u64 z=0;
			scanf("%llu", &z);
			assert(z>0);
			a[i] = 0;
			while (z > 0 && !isprime(z)) {
				z--; a[i]++;
			}
//			assert(a[i] > 0);
fprintf(STDERR, "%llu\n", a[i]);
			if (a[i] <= K) yes=1;
		}

		int nooo=1;
		for (int i = 0; i < N; i++) if (a[i] != 0) nooo=0;
		if (nooo) { printf("NO\n"); continue; }

		x = 0;
		for (int i = 0; i < N; i++) x ^= a[i]%(K+1);

		if (yes)
			printf("YES\n");
		else
			printf((x==0)?"NO\n":"YES\n");
	}
}
