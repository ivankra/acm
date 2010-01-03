#include <cstdio>
#include <cstdlib>
#include <ctime>

/* Mersenne Twister random numbers generator. */
struct Random {
	unsigned S[624], P;

	RNG(bool sr = true) {
		if (sr) srand(time(NULL));
		for (P = 0; P < 624; P++) S[P] = (rand() << 16) ^ rand();
	}

        /* Random 32-bit unsigned integer. */
	unsigned urand() {
		if (P >= 624) {
#define TW(a, b, c) \
	{ unsigned y = (S[a] & 0x80000000) | (S[b] & 0x7fffffff); \
	  S[a] = S[c] ^ (y >> 1) ^ (0x9908b0df & -(y & 1)); }
			for (int k = 0; k < 227; k++) TW(k, k+1, k+397)
			for (int k = 227; k < 623; k++) TW(k, k+1, k-227)
			TW(623, 0, 396)
			P = 0;
#undef TW
		}

		unsigned r = S[P++];
		r ^= r >> 11;
		r ^= (r << 7) & 0x9d2c5680;
		r ^= (r << 15) & 0xefc60000;
		return r ^ (r >> 18);
	}

        /* [a,b] */ int irand(int a, int b) { return a + (int)(urand()%(unsigned)(b-a+1)); }
	/* [0,b) */ int irand(int b) { return (int)(urand()%(unsigned)b); }
	/* [0,1] */ double drand() { return (urand()*2097152. + (urand()>>11)) / 9007199254740992.; }
	/* [a,b] */ double drand(double a, double b) { return a+(b-a)*drand(); }
};
