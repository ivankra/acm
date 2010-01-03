// Topological sorting.
#include <cstdio>
#include <cstring>
#include <cassert>

int L=1, R=2, U=4, D=8;
int out[128][128], G[128][128], n, ok, cnt;

void go(int y, int x) {
        if (out[y][x] > 0) return;
        if (out[y][x] == 0) { ok = 0; return; }

        out[y][x] = 0;
        if (G[y][x] & L) go(y, x-1);
        if (G[y][x] & R) go(y, x+1);
        if (G[y][x] & U) go(y-1, x);
        if (G[y][x] & D) go(y+1, x);

        cnt++;
        out[y][x] = cnt;
}

int get() {
        for (;;) {
                int c = getchar();
                assert(c != EOF);
                if (strchr("<>^v", c) != NULL) return c;
        }
}

int main()
{
        scanf("%d", &n);
        assert(n <= 120);

        memset(G, 0, sizeof(G));
        for (int r = 0; r < n; r++) {
                for (int c = 0; c < n-1; c++)
                        if (get() == '<') G[r][c+1] |= L; else G[r][c] |= R;
                if (r == n-1) break;
                for (int c = 0; c < n; c++)
                        if (get() == '^') G[r+1][c] |= U; else G[r][c] |= D;
        }

        memset(out, 0xff, sizeof(out));
        ok = 1;

        cnt = 0;
        for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
                go(i, j);

        if (ok) {
                for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                        printf(j+1<n?"%d ":"%d\n", out[i][j]);
        } else {
                printf("-1\n");
        }

        return 0;
}
