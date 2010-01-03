#include <cstdio>
#include <cstring>

static inline bool in(int x, int a, int b) { return a <= x && x <= b; }

#define N 512

int a[N][N], relab[N*N/3+10], T;

void go(int y1, int y2, int x1, int x2, int y, int x, int n)
{
        if (n <= 0) return;

        int s = 1<<(n-1);
        int t = ++T;

        if (in(y, y1,y1+s-1) && in(x, x1,x1+s-1)) {
                go(y1,y1+s-1, x1,x1+s-1, y,x, n-1);
        } else {
                go(y1,y1+s-1, x1,x1+s-1, y1+s-1,x1+s-1, n-1);
                a[y1+s-1][x1+s-1] = t;
        }

        if (in(y, y1+s,y2) && in(x, x1,x1+s-1)) {
                go(y1+s,y2, x1,x1+s-1, y,x, n-1);
        } else {
                go(y1+s,y2, x1,x1+s-1, y1+s,x1+s-1, n-1);
                a[y1+s][x1+s-1] = t;
        }

        if (in(y, y1,y1+s-1) && in(x, x1+s,x2)) {
                go(y1,y1+s-1, x1+s,x2, y,x, n-1);
        } else {
                go(y1,y1+s-1, x1+s,x2, y1+s-1,x1+s, n-1);
                a[y1+s-1][x1+s] = t;
        }

        if (in(y, y1+s,y2) && in(x, x1+s,x2)) {
                go(y1+s,y2, x1+s,x2, y,x, n-1);
        } else {
                go(y1+s,y2, x1+s,x2, y1+s,x1+s, n-1);
                a[y1+s][x1+s] = t;
        }
}

int main()
{
        int n, y, x;

        scanf("%d %d %d", &n, &y, &x);
        if (n < 0 || y < 1 || y > (1 << n) || x < 1 || x > (1 << n)) {
                printf("-1\n");
                return 0;
        }

        y--; x--;
        T = 0;
        go(0,(1<<n)-1, 0,(1<<n)-1, y,x, n);
        a[y][x] = 0;

        memset(relab, 0, sizeof(relab));
        for (int y = 0, z = 1; y < (1<<n); y++)
                for (int x = 0; x < (1<<n); x++)
                        if (a[y][x] != 0 && relab[a[y][x]] == 0)
                                relab[a[y][x]] = z++;

        for (int y = 0; y < (1<<n); y++) {
                for (int x = 0; x < (1<<n); x++)
                        printf(x ? " %d" : "%d", relab[a[y][x]]);
                printf("\n");
        }

        return 0;
}
