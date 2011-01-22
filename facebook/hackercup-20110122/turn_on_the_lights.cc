// Brute force all 2^18 ways of flipping switches in the first row,
// that uniquely determines what switches to flip in all subsequent rows.
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int INF = 999999999;
int nrows, ncols;
int rows[100], bitcount[1<<18], diffuse[1<<18];

const char *str(int mask)
{
    static char buf[100];
    for (int i = ncols - 1; i >= 0; i--) {
        buf[i] = (mask & 1) ? 'X' : '.';
        mask >>= 1;
    }
    return buf;
}


int f_diffuse(int mask)
{
    int res = (mask & 1) ? 3 : 0;
    for (int i = 1; i < 18; i++) {
        if (mask & (1 << i))
            res ^= 7 << (i - 1);
    }
    return res;
}

int solve(int mask)
{
    int all = (1 << ncols) - 1;
    int prev_mask = 0, next_mask;
    int flips = bitcount[mask];

    for (int row = 1; row <= nrows; row++) {
        next_mask = rows[row-1] ^ (diffuse[mask] & all) ^ prev_mask ^ all;
        flips += bitcount[next_mask];
        prev_mask = mask;
        mask = next_mask;
    }

    return mask == 0 ? flips : INF;
}

int main()
{
    int T;
    scanf("%d", &T);

    bitcount[0] = 0;
    for (int mask = 1; mask < (1 << 18); mask++)
        bitcount[mask] = 1 + bitcount[mask & (mask - 1)];

    for (int mask = 0; mask < (1 << 18); mask++)
        diffuse[mask] = f_diffuse(mask);

    for (int cs = 1; cs <= T; cs++) {
        scanf("%d %d", &nrows, &ncols);
        assert(nrows <= 18 && ncols <= 18);

        for (int i = 0; i < nrows; i++) {
            char buf[100];
            scanf(" %s", buf);
            assert(strlen(buf) == ncols);

            rows[i] = 0;
            for (int j = 0; j < ncols; j++) {
                if (buf[j] == 'X')
                    rows[i] = rows[i] * 2 + 1;
                else
                    rows[i] = rows[i] * 2;
            }
        }

        int best = INF;
        for (int mask = 0; mask < (1 << ncols); mask++)
            best = min(best, solve(mask));
        printf("%d\n", best == INF ? -1 : best);
        fflush(stdout);
    }
}
