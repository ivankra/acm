#include <stdio.h>

int main()
{
        char name[32][32];
        int n, m, d[32][32], x, y, z;
        for (int cs = 1; scanf("%d %d", &n, &m) == 2 && n > 0; cs++) {
                for (int i = 1; i <= n; i++) scanf(" %s", name[i]);

                for (int i = 1; i <= n; i++) {
                        for (int j = 1; j <= n; j++)
                                d[i][j] = 0x3fffffff;
                        d[i][i] = 0;
                }

                while (m-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3)
                        if (d[x][y] > z) d[x][y] = d[y][x] = z;

                for (int k = 1; k <= n; k++)
                for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                        d[i][j] <?= d[i][k] + d[k][j];

                int best = 1, res = 0x7fffffff;
                for (int x = 1; x <= n; x++) {
                        int s = 0;
                        for (int y = 1; y <= n; y++) s += d[y][x];
                        if (s < res) { res = s; best = x; }
                }

                printf("Case #%d : %s\n", cs, name[best]);
        }
}
