#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#include <set>
using namespace std;
typedef long long LL;
LL INF = 0x3FFFFFFFFFFFFFFFLL;

#define MAXDP 2000

LL FenceLen;
int N, Board[101];
LL dp[MAXDP];

LL solve() {
    LL res = INF;

    memset(dp, 0xff, sizeof(dp));
    dp[0] = 0;

    Board[N] = 0x7FFFFFFF;

    for (int i = 1; i <= MAXDP && i <= FenceLen; i++) {
        dp[i] = INF;
        for (int j = 0; /*j < N &&*/ Board[j] <= i; j++) {
            dp[i] = min(dp[i], 1 + dp[i - Board[j]]);
        }

        if (FenceLen >= i) {
            //for (int j = N; j < N; j++)
            int j = N - 1;
            {
                if ((FenceLen - i) % Board[j] == 0) {
                    res = min(res, dp[i] + (FenceLen - i) / Board[j]);
                }
            }
        }
    }

    return res;
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int cs = 1; cs <= T; cs++) {
        scanf("%lld %d", &FenceLen, &N);
        for (int i = 0; i < N; i++)
            scanf("%d", &Board[i]);
        sort(Board, Board+N);

        LL res = solve();
        if (res >= INF)
            printf("Case #%d: IMPOSSIBLE\n", cs);
        else
            printf("Case #%d: %lld\n", cs, res);
        fflush(stdout);
    }
}
