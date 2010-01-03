#include <stdio.h>

#define INF 0x3fffffff

struct Pair {
        int d, t;
        Pair(int d=0, int t=0) : d(d), t(t) {}
};

Pair operator +(const Pair &p, const Pair &q) { return Pair(p.d+q.d, p.t+q.t); }
bool operator <(const Pair &p, const Pair &q) {
//        return (p.d < q.d) || (p.d == q.d && p.t < q.t);
        return (p.t < q.t) || (p.t == q.t && p.d < q.d);
}

int main()
{
        int t, cs=1, x, y, n, m, et, ed;
        Pair D[32][32];
        for (scanf("%d", &t); cs <= t; cs++) {
                if (cs > 1) printf("\n");

                scanf("%d %d", &n, &m);

                for (int i = 1; i <= n; i++) {
                        for (int j = 1; j <= n; j++)
                                D[i][j] = Pair(INF, INF);
                        D[i][i] = Pair(0, 0);
                }

                while (m-- > 0 && scanf("%d %d %d %d", &x, &y, &et, &ed) == 4)
                        if (Pair(ed, et) < D[x][y])
                                D[x][y] = D[y][x] = Pair(ed, et);

                for (int k = 1; k <= n; k++)
                for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                        if (D[i][k] + D[k][j] < D[i][j])
                                D[i][j] = D[i][k] + D[k][j];

                for (scanf("%d", &m); m-- > 0 && scanf("%d %d", &x, &y) == 2;) {
                        if (D[x][y].d < INF)
                                printf("Distance and time to reach destination is %d & %d.\n", D[x][y].d, D[x][y].t);
                        else
                                printf("No Path.\n");
                }
        }
}
