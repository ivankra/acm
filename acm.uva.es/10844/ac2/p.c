#include <stdio.h>
#include <string.h>

#define LMASK   0x7FFFFFFF
#define LSHIFT  31

typedef unsigned long long u_int64_t;
typedef unsigned int u_int32_t;

typedef struct {
        int n;
        u_int32_t a[192];
} num_t;

static char *fmt(num_t *x)
{
        static char s1[16384], s2[16384];
        static num_t t;
        int i, k;
        u_int32_t r;
        u_int64_t c;

        for (t.n = x->n, i = 0; i < t.n; i++)
                t.a[i] = x->a[i] & LMASK;

        for (k = 0;;) {
                for (i = t.n - 1, c = 0; i >= 0; i--) {
                        c = (c << LSHIFT) | (u_int64_t)t.a[i];
                        t.a[i] = c / 1000000000ULL;
                        c %= 1000000000ULL;
                }
                r = (u_int32_t)c;

                for (i = 0; i < 9; i++, r /= 10)
                        s1[k++] = (r % 10) + '0';

                while (t.n > 0 && t.a[t.n - 1] == 0) t.n--;
                if (t.n <= 0) break;
        }

        for (k--; k > 0 && s1[k] == '0'; k--);

        for (i = 0; k >= 0;)
                s2[i++] = s1[k--];
        s2[i] = '\0';

        return s2;
}

static void set(num_t *x, unsigned c)
{
        x->n = (c == 0) ? 0 : 1;
        x->a[0] = c;
}

static void add(num_t *z, const num_t *x, const num_t *y)
{
        register int i;
        register u_int32_t c;

/*      if (x->n < y->n) {
                add(z, y, x);
                return;
        }
*/

        for (i = 0, c = 0; i < y->n; i++, c >>= LSHIFT)
                z->a[i] = (c += x->a[i] + y->a[i]) & LMASK;

        for (; i < x->n; i++, c >>= LSHIFT)
                z->a[i] = (c += x->a[i]) & LMASK;

        if (c)
                z->a[i++] = c;

        z->n = i;
}

static num_t res[902];

static void mktab()
{
        static num_t tab1[1024], tab2[1024];
        num_t *tab, *next;
        int n, i;

        tab = tab1;
        next = tab2;

        set(&res[1], 1);
        set(&res[2], 2);

        set(&tab[1], 2);

        for (n = 2;;) {
                add(&next[1], &res[n], &res[n - 1]);

                for (i = 2; i < n; i++)
                        add(&next[i], &next[i - 1], &tab[i - 1]);

                add(&res[n + 1], &next[n - 1], &res[n]);
                n++;

                if (n >= 900) break;

                tab = next;
                next = (next == tab1) ? tab2 : tab1;
        }
}

int main()
{
        int n;

        mktab();

        while (scanf("%d", &n) == 1 && n >= 1)
                printf("%d, %s\n", n, fmt(&res[n]));

        return 0;
}
