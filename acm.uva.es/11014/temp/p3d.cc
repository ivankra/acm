#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long i64;

i64 a[100001];

int main()
{
        a[0] = 0;
        a[1] = 26;
        for (i64 n = 2; n <= 100000; n++) {
                a[n] = a[n-1] + 24*n*n+2 - 26;

//                (x,y,z) = g
                for (int d = 2; d*d <= n; d++) if (n%d == 0) {
                        a[n] -= a[n/d] - a[n/d-1];
                        if (d*d != n) {
                                int e = n/d;
                                a[n] -= a[n/e] - a[n/e-1];
                        }
                }


/* [n/g] = a;  a <= n/g < a+1;  ag <= n <= (a+1)g-1;  (n+1)/(a+1) <= g <= n/a
  floor (n+a+1)/(a+1) <= g <= floor n/a  */
/*                for (int g = 2, h, t; g <= n; g = h) {
                        t=n/g; h=n/t+1;
                        a[n] -= (h-g)*a[t];
                }*/
        }

        i64 n;
        while (scanf("%lld", &n) == 1 && n > 0)
                printf("%lld\n", a[n/2]);
}
