#include <cstdio>
#include <cstring>

char s[128];
int memo[82][82];

int doit(int a, int b) {
        int &ret = memo[a][b];
        if (ret != -1) return ret;

        if (a > b) return ret = 0;
        if (a == b) return ret = 1;

        int m = b-a+1;

        ret = m;
        for (int c = a; c < b; c++)
                ret <?= doit(a,c) + doit(c+1,b);

        for (int p = 1; p < m; p++) {
                if ((m%p) != 0) continue;

                int k;
                for (k = 0; k < m; k++)
                        if (s[a+k] != s[a+(k%p)]) break;
                if (k < m) continue;

                ret <?= doit(a, a+p-1);
        }

        return ret;
}

int main()
{
        while (scanf(" %s", s) == 1 && s[0] != '*') {
                memset(memo, 0xff, sizeof(memo));
                printf("%d\n", doit(0, strlen(s)-1));
        }
}
