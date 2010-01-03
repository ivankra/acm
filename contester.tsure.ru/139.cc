#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
        int a, b;
        scanf("%d %d", &a, &b);
        if (a > b) swap(a, b);
        a += a & 1;
        b -= b & 1;
        printf("%d\n", a<=b ? (b-a)/2+1 : 0);
        return 0;
}
