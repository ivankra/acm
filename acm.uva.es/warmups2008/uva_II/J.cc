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
    long long y, N, bestX, bestY;
    while (cin >> N && N > 0) {
        bestY = LLONG_MAX;
        for (int hh = 1; cube(hh) <= N; hh++) {
            if (N % hh != 0) continue;
            LL h = hh;

            LL D = 9LL*h*h - 12LL*(h*h-N/h);
            if (D < 0) continue;

            LL sqrtD = (LL)sqrt((long double)D);
            if (sqrtD * sqrtD != D) continue;

            y = -3LL*h + sqrtD;
            if (y % 6 == 0 && y >= 6 && y/6 < bestY) {
                bestY = y/6;
                bestX = y/6 + h;
            }
            
            y = -3LL*h - sqrtD;
            if (y % 6 == 0 && y >= 6 && y/6 < bestY) {
                bestY = y/6;
                bestX = y/6 + h;
            }
        }

        if (bestY == LLONG_MAX)
            printf("No solution\n");
        else
            printf("%lld %lld\n", bestX, bestY);
    }
}
