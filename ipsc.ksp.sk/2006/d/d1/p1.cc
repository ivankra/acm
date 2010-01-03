#include <cstdio>
#include <cassert>
#include <cstring>
#include <gmp.h>

int main() {
	int N, K, L, T;
	for (scanf("%d", &T); T-- > 0;) {
		scanf("%d %d %d", &N, &K, &L);

		mpz_t f;
		mpz_init(f);
		mpz_fac_ui(f, N);

		char *s = mpz_get_str(NULL, 10, f);
		int m = strlen(s);

		assert(K <= m && L <= m);

		for (int i = 0; i < K; i++) putchar(s[i]);
		putchar(' ');
		for (int i = L-1; i >= 0; i--) putchar(s[m-1-i]);
		putchar('\n');
	}
}
