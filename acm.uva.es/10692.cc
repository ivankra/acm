#include <cstdio>
#define INF 0x3fffffff
using namespace std;

// returns b^e (mod m)
int modexp(int b, int e, int m) {
        int r;
        for (r = 1; e > 0; e >>= 1) {
                if (e & 1) r = (r * b) % m;
                b = (b * b) % m;
        }
        return r;
}

// return exact value of b^e, or INF if result is too big (> 10^4).
int pw(int b, int e) {
        if (b == 1 || e == 0) return 1;
        if (b == INF) return INF;

        int r = 1;
        while (e-- && r < 10001) r *= b;

        return (r < 10001) ? r : INF;
}

int a[16], n;
int exact[16];    // exact[i] = value of a[i]^...^a[n-1], or INF if it's too big.

// computes (a[i] ^ a[i+1] ^ ... ^ a[n-1]) modulo mod
int solve(int pos, int mod) {
        if (mod <= 1) return 0;
        if (exact[pos] < INF) return exact[pos] % mod;

        // if the exponent is small, do a usual modexp().
        if (exact[pos+1] < INF) return modexp(a[pos], exact[pos+1], mod);

        // otherwise, if exponent is large, the resulting number will be
        // a part of cycle (not of precycle),

        int b = a[pos];                 // base
        int p = modexp(b, 2*mod, mod);  // an element, which is certainly a part of the period

        // find length of period
        int k = 0;
        for (int q = p;;) {
                k++;
                q = (q * b) % mod;
                if (q == p) break;
        }

        int e = 50000 - (50000 % k);
        return modexp(b, e + solve(pos+1, k), mod);
}

int main() {
        int m;
        for (int cs = 1; scanf("%d %d", &m, &n) == 2 && n > 0 && m > 0; cs++) {
                for (int i = 0; i < n; i++) scanf("%d", &a[i]);

                exact[n] = 1;
                for (int i = n-1; i >= 0; i--)
                        exact[i] = pw(a[i], exact[i+1]);

                printf("Case #%d: %d\n", cs, solve(0, m));
        }
        return 0;
}
