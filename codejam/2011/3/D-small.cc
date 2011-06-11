#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

char s[100];

bool is_square(long long x) {
    long double xx = sqrt((long double)x);
    long long xxx = (long long)xx;
    return xxx * xxx == x;
}

bool rec(int i, long long x)
{
    if (s[i] == 0) {
        return is_square(x);
    }

    for (int c = 0; c <= 1; c++) {
        if (s[i] != '?' && s[i] != '0' + c)
            continue;

        char orig = s[i];

        s[i] = '0' + c;
        if (rec(i+1, x*2 + c))
            return true;

        s[i] = orig;
    }

    return false;
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int cs = 1; cs <= T; cs++) {
        scanf(" %s", s);
        if (!rec(0, 0))
            fprintf(stderr, "unsolvable %s\n", s);
        printf("Case #%d: %s\n", cs, s);
    }
}
