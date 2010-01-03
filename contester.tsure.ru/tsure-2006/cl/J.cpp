// O(n^3) dp
#include <cstdio>
#include <cstring>
typedef __int64 i64;

i64 memo[16][16][16];

i64 doit(int R, int C, int P) {
        if (R < 0 || P < 0 || P > R) return 0;

        i64 &ret = memo[R][C][P];
        if (ret != -1) return ret;
        if (C == 0) return ret = (R >= 0 && P == 0) ? 1 : 0;

        ret = 0;
        if (P >= 2)      ret += P*(P-1)/2 * doit(R-2, C-1, P-2);
        if (P*(R-P) > 0) ret += P*(R-P) * doit(R-1, C-1, P);
        if (R-P >= 2)    ret += (R-P)*(R-P-1)/2 * doit(R, C-1, P+2);
        return ret;
}

int main()
{
        int N;
        scanf("%d", &N);
        memset(memo, 0xff, sizeof(memo));
        printf("%I64d\n", doit(N,N,0));
        return 0;
}
