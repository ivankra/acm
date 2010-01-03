#include <stdio.h>
#include <algorithm>
using namespace std;

int gcd(int x, int y) { return (x==0&&y==0?0:__gcd(abs(x), abs(y))); }

int main() {
        int n;
        while (scanf("%d", &n) == 1 && n > 0) {
                n/=2;
                int ret = 0;
                for (int x = -n; x <= n; x++)
                for (int y = -n; y <= n; y++)
                for (int z = -n; z <= n; z++)
                        if (gcd(x, gcd(y, z)) == 1) printf("%d %d %d\n", x,y,z);
        }
}
