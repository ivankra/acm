// Knapsack-like DP.
#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
        int f[4501]={0};
        for (int i = 1; i <= 4500; i++) f[i] = 99;

{        for (int x = 1; x <= 5; x++)
        for (int y = x; y <= 5; y++) {
                int A = x*60/y, B = y*60/x;
                for (int s = 4500; s >= 0; s--) {
                        if (s-A >= 0) f[s] = min(f[s], 1+f[s-A]);
                        if (s-B >= 0) f[s] = min(f[s], 1+f[s-B]);
                }
        }
}
        int t, x, y;
        for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &x, &y) == 2;) {
                x = x*60/y;
                if ((60 % y) != 0 || x<0 || x>4500 || f[x] > 15)
                        printf("-1\n");
                else
                        printf("%d\n", f[x]);
        }

        return 0;
}
