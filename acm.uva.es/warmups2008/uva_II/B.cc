#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long LL;
#define FOREACH(it, v) for(typeof((v).begin())it=(v).begin();it!=(v).end();++it)
#define SIZE(v) ((int)(v).size())
#define ALL(v) (v).begin(), (v).end()
#define REP(i,n) for(int i=0;i<(n);++i)

LL cube(LL x) { return x*x*x; }
int main()
{
    long long x, y, N;
    while (cin >> N && N > 0) {
        for (y = 1; ; y++) {
            if (cube(y+1) - cube(y) > N) break;
            for (x = y+1; cube(x) - cube(y) < N; x++);
            if (cube(x) - cube(y) == N) {
                printf("%lld %lld\n", x, y);
                goto done;
            }
        }
        printf("No solution\n");
done:;
    }
}
