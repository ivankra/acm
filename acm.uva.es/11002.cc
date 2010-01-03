#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int can[64][64], a[64][64], n, seen[64*6000], seen_id=42;
int buf1[64*6000], buf2[64*6000], *Q, *R;

int main()
{
        memset(seen, 0, sizeof(seen));
        while (scanf("%d", &n) == 1 && n > 0) {
                memset(a, 0, sizeof(a));
                memset(can, 0, sizeof(can));
                for (int i = 0; i < n; i++) {
                        for (int j = 0; j <= i; j++) {
                                scanf("%d", &a[i][j]);
                                can[i][j] = 1;
                        }
                }

                for (int i = 1; i < n; i++) {
                        for (int j = i; j < n; j++) {
                                scanf("%d", &a[n+i-1][j]);
                                can[n+i-1][j] = 1;
                        }
                }

                n = 2 * n - 1;

                seen_id++;
                Q = buf1;
                seen[Q[0] = (a[0][0] + 3000) << 6] = seen_id;
                Q[1] = -1;

                for (int row = 1; row < n; row++) {
                        int *Rt = R = (Q == buf1) ? buf2 : buf1;
                        seen_id++;
                        for (; *Q >= 0; Q++) {
                                for (int sh = 0; sh < 2; sh++) {
                                        int col = ((*Q) & 63) + sh;
                                        if (!can[row][col]) continue;
                                        for (int sgn = -1; sgn <= 1; sgn += 2) {
                                                int sum = ((*Q) >> 6) + sgn * a[row][col];
                                                int x = (sum << 6) | col;
                                                if (seen[x] == seen_id) continue;
                                                seen[x] = seen_id;
                                                *Rt++ = x;
                                        }
                                }
                        }
                        *Rt = -1;
                        Q = R;
                }

                int best = 0x7fffffff;
                for (; *Q >= 0; Q++)
                        best <?= abs(((*Q) >> 6) - 3000);
                printf("%d\n", best);
        }
}
