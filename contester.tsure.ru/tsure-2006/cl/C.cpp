// DP+bignums
#include <cstdio>
#include <cstring>
#include <cassert>

#define RADIX 1000000000
#define LIMBS 15

struct Bignum {
        unsigned a[LIMBS];
        int n;
        Bignum &operator =(int y) { a[0] = y; n = 1; return *this; }
        Bignum &operator +=(const Bignum &y) {
                while (n < y.n) a[n++] = 0;
                unsigned c = 0; int i;
                for (i = 0; i < y.n; i++) {
                        c += a[i] + y.a[i];
                        if (c >= RADIX) { a[i]=c-RADIX; c=1; } else { a[i]=c; c=0; }
                }
                while (c > 0) {
                        if (i == n) { assert(n < LIMBS); a[n++] = c; break; }
                        if (a[i] < RADIX-1) { a[i]++; break; }
                        a[i++] = 0;
                }
                return *this;
        }
};

void prn(const Bignum &x) {
        int i;
        for (i = x.n-1; i > 0 && x.a[i] == 0; i--);
        for (int j = 0; i >= 0; i--) printf(j++ ? "%.9u" : "%u", x.a[i]);
        printf("\n");
}
        
int world[256][256];

int main()
{
        int n, m;
        scanf("%d %d", &n, &m);

        for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
                int c;
                while ((c = getchar()) != EOF && c != '.' && c != '#');
                assert(c != EOF);
                world[i][j] = c;
        }

        int MANy, MANx, UNIy, UNIx;

        scanf("%d %d %d %d", &MANy, &MANx, &UNIy, &UNIx);
        if (MANx > UNIx || MANy > UNIy) { printf("0\n"); return 0; }

        Bignum tab[256];
        for (int i = 0; i <= m+1; i++) tab[i] = 0;
        tab[UNIx] = 1;

        for (int row = UNIy; row >= MANy; row--)
        for (int col = m; col >= 1; col--)
                if (world[row][col] == '#')
                        tab[col] = 0;
                else
                        tab[col] += tab[col+1];

        prn(tab[MANx]);
        return 0;
}
