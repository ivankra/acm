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
typedef unsigned long long ULL;
#define FOREACH(it, v) for(typeof((v).begin())it=(v).begin();it!=(v).end();++it)
#define SIZE(v) ((int)(v).size())
#define ALL(v) (v).begin(), (v).end()
#define REP(i,n) for(int i=0;i<(n);++i)

ULL memo[34][34][2][2];
char got[34][34][2][2];
int G, D;

ULL f(int A, int B, int first, int cur)
{
    if (A + B == 0) return first == cur ? 1 : 0;

    ULL &res = memo[A][B][first][cur];
    if (got[A][B][first][cur]) return res;
    got[A][B][first][cur] = 1;
    res = 0;

    if (cur == 0) {
        for (int k = 1; k <= A && (B == 0 || k <= G); k++)
            res += f(A-k, B, first, 1);
    } else {
        for (int k = 1; k <= B && (A == 0 || k <= G); k++)
            res += f(A, B-k, first, 0);
    }

    return res;
}

ULL solve()
{
    memset(got, 0, sizeof(got));

    if (D <= 0) return 1;
    if (G == 0) return 0;

    return f(D, D, 0, 0) + f(D, D, 1, 1);
}

int main()
{
    for (int cs = 1; ((cin >> D >> G) && G >= 0); cs++) {
        printf("Case %d: %llu\n", cs, solve());
    }
}
