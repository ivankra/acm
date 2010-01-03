/*
ID: infnty1
PROB: buylow
LANG: C++
*/
#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

void relabel(int a[], int n) {
        map<int, int> m;
        int i;
        for (i = 0; i < n; i++) m[a[i]] = -1;

        i = 0;
        for (map<int, int>::iterator it = m.begin(); it != m.end(); it++, i++)
                it->second = i;

        for (i = 0; i < n; i++)
                a[i] = m[a[i]];
}

#define RADIX 1000000000

struct Big {
        int n;
        unsigned a[63];

        void operator =(int x) { n=1; a[0]=x; }
        void operator +=(const Big &x) {
                unsigned c=0;
                while (n < x.n) a[n++] = 0;
                for (int i = 0; i < x.n; i++, c /= RADIX)
                        a[i] = (c += a[i] + x.a[i]) % RADIX;
                for (int i = x.n; c > 0; i++, c /= RADIX) {
                        if (i >= x.n) { assert(n<63); a[n++] = c; break; }
                        a[i] = (c += a[i]) % RADIX;
                }
        }

        void print() {
                int i;
                for (i = n-1; i > 0 && a[i] == 0; i--);
                for (printf("%u", a[i]); i-- > 0;) printf("%.9u", a[i]);
                printf("\n");
        }
};

int a[5010], s[5010], got[5010], n;
Big w[5010];

int main()
{
        freopen("buylow.in", "r", stdin);
        freopen("buylow.out", "w", stdout);

        scanf("%d", &n);
        for (int i = 0; i < n; i++)
                scanf("%d", &a[i]);

        relabel(a, n);

        memset(got, 0xff, sizeof(got));
        a[n] = -1;
        for (int i = 0; i <= n; i++) {
                s[i] = 1;
                for (int j = i-1; j >= 0; j--)
                        if (a[j] > a[i]) s[i] >?= 1 + s[j];

                if (s[i] == 1) { w[i] = 1; continue; }

                w[i] = 0;
                for (int j = i-1; j >= 0; j--) {
                        if (a[j] <= a[i] || s[i] != 1 + s[j]) continue;
                        if (got[a[j]] == i) continue;
                        got[a[j]] = i;
                        w[i] += w[j];
                }
        }

        printf("%d ", s[n]-1);
        w[n].print();

        return 0;
}
