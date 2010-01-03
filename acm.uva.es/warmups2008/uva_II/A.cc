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

int main()
{
    double dp[128][128];
    int pnum,pden,n,T;
    scanf("%d", &T);

    for (int cs = 1; cs <= T; cs++) {
        scanf(" %d / %d %d", &pnum, &pden, &n);
        double p = pnum / (double)pden;

        for (int g = n; g >= 0; g--) {
            for (int w = 0; w <= g; w++) {
                if (w*pden > pnum*g) {
                    dp[g][w] = 1;
                    continue;
                }

                dp[g][w] = 0;
                if (g == n) continue;

                dp[g][w] = p * dp[g+1][w+1] + (1-p) * dp[g+1][w];
            }
        }

        double z = dp[0][0];

        double ans = 1 / (1 - z);
        //for (int i = 1; i <= 100000; i++)
        //    ans += i * pow(z, i-1) * (1-z);
        printf("Case #%d: %.0f\n", cs, floor(ans + 1e-6));
    }

}
