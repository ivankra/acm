#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long i64;

i64 a[100001];

int main()
{
        a[0] = 0;
        for (i64 n = 1, c = 0; n <= 100000; n++) {
                c += 24*n*n+2;
                a[n] = c;

/*
[n/g] = a
a <= n/g < a+1
ag <= n <= (a+1)g-1
(n+1)/(a+1) <= g <= n/a
floor (n+a+1)/(a+1) <= g <= floor n/a
*/
                for (int g = 2, h, t; g <= n; g = h) {
                        t=n/g; h=n/t+1;
                        a[n] -= (h-g)*a[t];
                }

/*                for (int g = 2; g <= n; g++)
                        a[n] -= a[n/g];
*/
        }

        i64 n;
        while (scanf("%lld", &n) == 1 && n > 0)
                printf("%lld\n", a[n/2]);
}
