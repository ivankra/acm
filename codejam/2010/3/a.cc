#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;
typedef long long LL;

LL Mod(LL x, LL p) {
    return (x % p + p) % p;
}

/* Extended GCD.  Finds x,y such that ax + by = g = gcd(a, b). */
template<typename T> void gcdext(T &g, T &x, T &y, T a, T b) {
	if (b == 0) {
		g = a; x = 1; y = 0;
	} else {
		gcdext(g, y, x, b, a % b);
		y = y - (a / b) * x;
	}
}

/* Finds g = gcd(a,b) and x,y such that ax + by = g (mod m). */
template<typename T> void gcdextm(T &g, T &x, T &y, T a, T b, T m) {
	if (b == 0) {
		g = a; x = 1; y = 0;
	} else {
		gcdextm(g, y, x, b, a % b, m);
		y -= ((a / b) * x) % m;
		while (y < 0) y += m;
	}
}

/* Modular inverse.
   Returns x such that ax = 1 (mod m), or -1 if no such x exists. */
template<typename T> T modinv(T a, T m) {
	T g, x, y;
	gcdextm(g, x, y, a, m, m);
	if (g < 0) g = -g;
	return (g == 1) ? (x % m) : -1;
}

/* Modular inverse.  Computes x such that ax = 1 (mod m).  Returns false if
   such x does not exist. */
template<typename T> bool modinv(T &x, T a, T m) {
	T g, y;
	gcdextm(g, x, y, a, m, m);
	if (g < 0) g = -g;
	if (g != 1) return false;
	x = x % m;
	return true;
}

char is_prime[1000100];
int N, D, S[1000];

bool check(int A, int B, int P, int *res) {
    for (int i = 0; i+1 < N; i++) {
        LL x = (A * (LL)S[i] + B) % P;
        if (x != S[i+1])
            return false;
    }

    LL x = (A * (LL)S[N-1] + B) % P;
    if (*res < 0 || *res == x) {
        *res = x;
        return false;
    } else {
        return true;
    }
}

int solve()
{
    int max_S = S[0];
    for (int i = 0; i < N; i++)
        max_S = max(max_S, S[i]);

    int ten_D = 1;
    for (int i = 0; i < D; i++)
        ten_D *= 10;

    if (N <= 1)
        return -1;

    int distinct_i = -1;
    for (int i = 0; i < N; i++) {
        if (S[i] != S[i+1] && i+2 < N) {
            distinct_i = i;
            break;
        }
    }

    if (distinct_i != -1) {
        int res = -2;

        for (int P = max_S + 1; P <= ten_D; P++) {
            if (!is_prime[P]) continue;

            LL A = Mod(modinv(
                Mod(S[distinct_i] - S[distinct_i + 1], P), (LL)P) *
                (LL)(S[distinct_i + 1] - S[distinct_i + 2]), P);
            LL B = Mod(S[1] - A * S[0], P);
            if (check(A, B, P, &res))
                return -1;
        }

        return res;
    }

    bool same = true;
    for (int i = 0; i < N; i++)
        if (S[i] != S[0])
            same = false;
    if (N >= 2 && same)
        return S[0];

    return -1;
}

int main()
{
    memset(is_prime, 1, sizeof(is_prime));
    is_prime[0] = 0;
    is_prime[1] = 0;
    for (int i = 2; i * i <= 1000000; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= 1000000; j += i)
                is_prime[j] = 0;
        }
    }

    int T;
    scanf("%d", &T);

    for (int cs = 1; cs <= T; cs++) {
        scanf("%d %d", &D, &N);
        for (int i = 0; i < N; i++)
            scanf("%d", &S[i]);

        int res = solve();
        if (res < 0)
            printf("Case #%d: I don't know.\n", cs);
        else
            printf("Case #%d: %d\n", cs, res);
    }
}
