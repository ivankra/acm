#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <algorithm>
using namespace std;

typedef long long LL;

int nrows, ncols, D, found;
char grid[512][512];

void check_odd(int y0, int x0)
{
    int max_size = min(x0+1, min(y0+1, min(nrows-y0, ncols-x0)));
    max_size = (max_size - 1) * 2 + 1;

    LL sumx = 0, sumy = 0;

#define ADD(y, x) { LL w = grid[y][x] + D; sumx += (x - x0) * w; sumy += (y - y0) * w; }

    for (int size = 3; size <= max_size; size += 2) {
        int h = (size - 1) / 2 - 1;
        ADD(y0 + h, x0 + h);
        ADD(y0 + h, x0 - h);
        ADD(y0 - h, x0 + h);
        ADD(y0 - h, x0 - h);
        h += 1;
        for (int k = -h+1; k < h; k++) ADD(y0 - h, x0 + k);
        for (int k = -h+1; k < h; k++) ADD(y0 + h, x0 + k);
        for (int k = -h+1; k < h; k++) { ADD(y0 + k, x0 - h); ADD(y0 + k, x0 + h); }

        if (sumx == 0 && sumy == 0) {
            if (size > found)
                found = size;
        }
    }

#undef ADD
}

void check_even(int y0, int x0)
{
    int max_size = min(x0, min(y0, min(nrows-y0, ncols-x0)))*2;
    LL sumx = 0, sumy = 0;

#define ADD(y, x) { LL w = grid[y][x] + D; sumx += (2*(x)+1 - 2*(x0)) * w; sumy += (2*(y)+1 - 2*(y0)) * w; }

    for (int size = 4; size <= max_size; size += 2) {
        int h = size / 2;

        h--;
        ADD(y0 + h-1, x0 + h-1);
        ADD(y0 + h-1, x0 - h);
        ADD(y0 - h, x0 + h-1);
        ADD(y0 - h, x0 - h);
        h++;

        for (int k = -h+1; k < h-1; k++) ADD(y0 - h, x0 + k);
        for (int k = -h+1; k < h-1; k++) ADD(y0 + h-1, x0 + k);
        for (int k = -h+1; k < h-1; k++) { ADD(y0 + k, x0 - h); ADD(y0 + k, x0 + h-1); }

        if (sumx == 0 && sumy == 0 && size >= 3) {
            if (size > found)
                found = size;
        }
    }

#undef ADD
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int cs = 1; cs <= T; cs++) {
        scanf("%d %d %d", &nrows, &ncols, &D);
        memset(grid, 0, sizeof(grid));
        for (int i = 0; i < nrows; i++) {
            scanf(" %s", grid[i]);
            for (int j = 0; j < ncols; j++)
                grid[i][j] -= '0';
        }

        found = 0;

        for (int i = 0; i < nrows; i++) {
            for (int j = 0; j < ncols; j++) {
                check_odd(i, j);
                check_even(i, j);
            }
        }

        if (found == 0)
            printf("Case #%d: IMPOSSIBLE\n", cs);
        else
            printf("Case #%d: %d\n", cs, found);
        fflush(stdout);
    }
}
