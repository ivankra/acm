#include <stdio.h>
#define INF 0x7FFFFFFF

/*
 *  Returns the maximal coverage for a given set of denominations
 *  Input:
 *    a[0]: number of denominations
 *    a[i] for i=1..a[0]: values of denominations (in arbitrary order)
 *    s: maximum number of stamps
 */
int get(int a[], int s)
{
        static int c[65536];
        int i, k;

        /* c[k] = the minimum number of stamps needed to cover the value 'k' */

        /* solution is by dynamic programming:
           c[0]=0,
           for k>0: c[k] = min_{1<=i<=a[0], k>=a[i]} (c[k-a[i]]+1) */

        for (c[0] = 0, k = 1;; k++) {
                for (c[k] = INF, i = 1; i <= a[0]; i++)
                        if (k >= a[i] && c[k] > c[k-a[i]]+1)
                                c[k] = c[k-a[i]] + 1;
                if (c[k] > s) return k-1;
        }
}

int main()
{
        static int a[16][16], c[16], n, s;
        int i, j;

        while (scanf("%d %d", &s, &n) == 2 && s > 0) {
                for (i = 0; i < n && scanf("%d", &a[i][0]) == 1; i++) {
                        for (j = 1; j <= a[i][0]; j++)
                                scanf("%d", &a[i][j]);
                        c[i] = get(a[i], s);
                }

                for (j = 0, i = 1; i < n; i++)
                        if ((c[i] > c[j]) ||
                            (c[i] == c[j] && a[i][0] < a[j][0]) ||
                            (c[i] == c[j] && a[i][0] == a[j][0] && a[i][a[i][0]] < a[j][a[j][0]]))
                                j = i;

                printf("max coverage =%4d :", c[j]);
                for (i = 1; i <= a[j][0]; i++) printf("%3d", a[j][i]);
                printf("\n");
        }

        return 0;
}
