// Binary search on length of LCS + monte-carlo.  O(n log^2 n).
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef unsigned long long u64;

char S[32768], T[32768];
int n, m;
u64 X[32768], Y[32768];

int f(int len, u64 mod) {
        u64 b = 1;
        for (int i = 0; i < len-1; i++) b = (26 * b) % mod;

        int Xn = 0;
        u64 h = 0;
        for (int i = 0; i < n; i++) {
                h = (26 * h + (S[i]-'a')) % mod;
                if (i >= len-1) {
                        X[Xn++] = h;
                        h = (h - (b * (S[i-len+1]-'a'))%mod + mod) % mod;
                }
        }

        int Yn = 0;
        h = 0;
        for (int i = 0; i < m; i++) {
                h = (26 * h + (T[i]-'a')) % mod;
                if (i >= len-1) {
                        Y[Yn++] = h;
                        h = (h - (b * (T[i-len+1]-'a'))%mod + mod) % mod;
                }
        }

        sort(X, X+Xn);
        sort(Y, Y+Yn);

        for (int i = 0, j = 0; i < Xn; i++) {
                Y[Yn] = X[i];
                while (Y[j] < X[i]) j++;
                if (j >= Yn) break;
                if (Y[j] == X[i]) return 1;
        }

        return 0;
}

int check(int l) {
        return f(l, 270215977642229791LL) &&
               f(l, 144115188074855903LL) &&
               f(l, 270215977642229813LL) &&
               f(l, 270215977642230421LL) &&
               f(l, 271828182845904523LL);
}

int main()
{
        scanf(" %s", S); n = strlen(S);
        scanf(" %s", T); m = strlen(T);

        int a = 0, b = min(n, m);
        while (a < b) {
                int c = (a + b + 1) / 2;
                if (check(c)) a = c; else b = c-1;
        }
        printf("%d\n", a);
        return 0;
}
