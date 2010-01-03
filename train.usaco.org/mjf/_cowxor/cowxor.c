/* let a[0], a[1], ..., a[n-1] be the sequence of cows' assigned numbers
   let b[k] = a[0] xor a[1] xor ... xor a[k-1], for k=0..n
   then a[i] xor a[i+1] xor ... xor a[j-1] = b[i] xor b[j]

   the problem reduces to finding a pair of integers (i,j), s.t.
     a) 0 <= i <= j <= n
     b) b[i] xor b[j] is maximized
     c) j is minimized
     d) i is maximized
   the answer to the original problem is the segment a[i]...a[j-1] */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define M       21              /* number of bits in cows' assigned numbers */
#define MAXN    100005
#define INF     0x7FFFFFFF

int a[MAXN], b[MAXN], c[(1 << M) + 1], d[MAXN], e[(1 << M) + 1], n;
int bestx, bestj;

int cmp(const void *p, const void *q) { return *(int *)p - *(int *)q; }

int main()
{
        int i, j, k;

        freopen("cowxor.in", "r", stdin);
        /*freopen("cowxor.out", "w", stdout);*/

        scanf("%d", &n);
        assert(1 <= n && n < MAXN);
        for (i = 0, b[0] = 0; i < n; i++) {
                scanf("%d", &a[i]);
                assert(0 <= a[i] && a[i] < (1 << M));
                b[i+1] = b[i] ^ a[i];
        }

        /* Compute c[k] = |{i: 0 <= i <= n, b[i] < k}|, for k=0..2^M */
        memcpy(d, b, (n+1) * sizeof(b[0]));
        qsort(d, n+1, sizeof(d[0]), &cmp);
        for (d[n+1] = INF, i = j = 0; i <= n;) {
                while (d[i] >= j) c[j++] = i;
                while (d[i] < j) i++;
        }
        while (j <= (1 << M)) c[j++] = i;

        /* Compute e[k] = min {i: 0 <= i <= n, b[i] = k }, for k=0..2^M */
        for (i = 0; i <= (1 << M); i++) e[i] = INF;
        for (i = 0; i <= n; i++) if (e[b[i]] > i) e[b[i]] = i;

        bestx = bestj = 0;
        for (j = 1; j <= n; j++) {
                /* find an integer k such that k xor b[j] is maximized and
                   c[k+1]-c[k] > 0  (i.e. there exists x, s.t. b[x]=k) */
                for (k = 0, i = M-1; i >= 0; i--)
                        if ((c[k+(1<<(i+1))] - c[k+(1<<i)]) > 0 &&   /* if i-th bit may be 1, and */
                            ((c[k+(1<<i)] - c[k]) == 0 ||            /* (it cannot be 0, or */
                             ((b[j] >> i) & 1) == 0))                /* it's desirable it's 1), */
                                k |= 1 << i;                         /* set i-th bit */
                assert(e[k] < INF);

                if (e[k] >= j || (k ^ b[j]) <= bestx) continue;
                bestj = j;
                bestx = k ^ b[j];
                if (bestx == ((1 << M) - 1)) break;
        }

        for (i = j = bestj; i >= 0 && (b[i] ^ b[j]) != bestx; i--);
        assert(i >= 0 && (b[i] ^ b[j]) == bestx);
        printf("%d %d %d\n", bestx, i+1, j);

        return 0;
}
