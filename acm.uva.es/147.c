#include <stdio.h>

static long long tab[6001];

static void make()
{
        static int m, v[] = { 2, 4, 10, 20, 40, 100, 200, 400, 1000, 2000, 0 };
        register int i, c;

        for (i = 0; i <= 6000; i++)
                tab[i] = 1;

        for (m = 0; v[m] != 0; m++) {
                c = v[m];

                for (i = c; i <= 6000; i++)
                        tab[i] += tab[i - c];
        }
}

int main()
{
        static int d, c;

        make();

        scanf(" %d.%d", &d, &c);
        printf("%lld\n", d, c, tab[d * 20 + (c / 5)]);

        return 0;
}
