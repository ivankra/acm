#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <cstring>
#include <cassert>
#include <climits>
using namespace std;
typedef long long LL;

int T, P, N, maxMiss[10000], price[10000], numMatches;
int round_id[10000], children[10000][2];

bool plays(int team, int match) {
    int x = team / 2;
    int size = N / 2;
    int st = 0;
    for (int round = 0; round < P; round++) {
        if (x == match) return true;
        x = (x - st) / 2 + st + size;
        st += size;
        size /= 2;
    }
    return false;
}

LL memo[10000][16];

LL f(int match_id, int missed) {
    LL &res = memo[match_id][missed];
    if (res != -1)
        return res;

    res = 1LL << 60;

    for (int buy = 0; buy <= 1; buy++) {
        int new_missed = missed + (1 - buy);
        LL cost = price[match_id] * buy;

        if (round_id[match_id] > 1) {
            cost += f(children[match_id][0], new_missed);
            cost += f(children[match_id][1], new_missed);
        } else {
            int a = 2 * match_id;
            int b = 2 * match_id + 1;
            if (new_missed > maxMiss[a] || new_missed > maxMiss[b])
                continue;
        }

        if (cost < res)
            res = cost;
    }

    return res;
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int cs = 1; cs <= T; cs++) {
        scanf("%d", &P);
        N = 1 << P;

        int numMatches = 0;
        for (int round = 1; round <= P; round++) {
            numMatches += N / (1 << round);
        }

        //fprintf(stderr, "P=%d N=%d num_matches=%d\n", P, N, numMatches);

        for (int i = 0; i < N; i++)
            scanf("%d", &maxMiss[i]);
        for (int i = 0; i < numMatches; i++)
            scanf("%d", &price[i]);

        memset(round_id, 0, sizeof(round_id));
        memset(children, 0xff, sizeof(children));
        for (int team = 0; team < N; team++) {
            int x = team / 2;
            int size = N / 2;
            int st = 0;
            for (int round = 0; round < P; round++) {
                round_id[x] = round + 1;
                int y = (x - st) / 2 + st + size;
                st += size;
                size /= 2;
                if (children[y][0] != x && children[y][1] != x) {
                    if (children[y][0] < 0)
                        children[y][0] = x;
                    else
                        children[y][1] = x;
                }
                x = y;
            }
        }

        for (int i = 0; i < numMatches; i++) {
            //printf("match %d: round=%d kids=%d,%d, price=%d\n", i, round_id[i], children[i][0], children[i][1], price[i]);
        }

        

        memset(memo, 0xff, sizeof(memo));
        printf("Case #%d: %lld\n", cs, f(numMatches-1, 0));
    }
}
